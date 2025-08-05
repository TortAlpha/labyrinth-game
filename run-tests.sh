#!/bin/bash

# Script for building and running tests for the Labyrinth Game project

set -e  # Stop execution on error

# Default values
QUIET_MODE=false
TEST_TYPE="unit"

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --quiet|-q)
            QUIET_MODE=true
            echo "Quiet mode enabled - suppressing verbose output"
            shift
            ;;
        unit|integration|all)
            TEST_TYPE="$1"
            shift
            ;;
        --help|-h)
            echo "Usage: $0 [OPTIONS] [TEST_TYPE]"
            echo ""
            echo "TEST_TYPE:"
            echo "  unit         Run unit tests only (default)"
            echo "  integration  Run integration tests only"
            echo "  all          Run both unit and integration tests"
            echo ""
            echo "OPTIONS:"
            echo "  --quiet, -q  Enable quiet mode"
            echo "  --help, -h   Show this help message"
            exit 0
            ;;
        *)
            echo "Unknown argument: $1"
            echo "Use --help for usage information"
            exit 1
            ;;
    esac
done

PROJECT_ROOT=$(dirname "$(readlink -f "$0" 2>/dev/null || echo "$0")")
BUILD_DIR="$PROJECT_ROOT/build"

echo "Setting up tests for Labyrinth Game project"
echo "Project root directory: $PROJECT_ROOT"

# Configure PKG_CONFIG_PATH for macOS Homebrew
if [[ "$OSTYPE" == "darwin"* ]]; then
    export PKG_CONFIG_PATH="/opt/homebrew/lib/pkgconfig:$PKG_CONFIG_PATH"
fi

# Check for CppUnit availability
if ! pkg-config --exists cppunit; then
    echo "ERROR: CppUnit not found. Please install CppUnit:"
    echo "  macOS: brew install cppunit"
    echo "  Ubuntu/Debian: sudo apt-get install libcppunit-dev"
    echo "  CentOS/RHEL: sudo yum install cppunit-devel"
    exit 1
fi

echo "CppUnit found"

# Create build directory
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir -p "$BUILD_DIR"
else
    echo "Using existing build directory..."
fi
cd "$BUILD_DIR"

# Configure project
echo "Configuring CMake..."
cmake .. -DBUILD_TESTS=ON

# Build
echo "Building tests..."
make

# Function to run unit tests
run_unit_tests() {
    echo "Running unit tests..."
    cd tests

    if [ -f "./run-tests" ]; then
        echo "=================================================="
        echo "           LABYRINTH GAME - UNIT TESTS           "
        echo "=================================================="
        echo
        
        # Capture test output
        TEST_OUTPUT=$(./run-tests 2>&1)
        TEST_RESULT=$?
        
        process_test_results "Unit"
    else
        echo "ERROR: Unit test executable not found"
        return 1
    fi
}

# Function to run integration tests  
run_integration_tests() {
    echo "Running integration tests..."
    
    # Check if integration tests are built
    if [ ! -d "$PROJECT_ROOT/integration-tests/build" ]; then
        echo "Building integration tests..."
        cd "$PROJECT_ROOT/integration-tests"
        mkdir -p build
        cd build
        cmake ..
        make
    else
        cd "$PROJECT_ROOT/integration-tests/build"
        echo "Using existing integration test build..."
        make
    fi

    if [ -f "./run-integration-tests" ]; then
        echo "=================================================="
        echo "      LABYRINTH GAME - INTEGRATION TESTS        "
        echo "=================================================="
        echo
        
        # Capture test output
        TEST_OUTPUT=$(./run-integration-tests 2>&1)
        TEST_RESULT=$?
        
        process_test_results "Integration"
    else
        echo "ERROR: Integration test executable not found"
        return 1
    fi
}

# Function to process test results
process_test_results() {
    local test_type="$1"
    
    # Count tests (strip any extra whitespace)
    TOTAL_TESTS=$(echo "$TEST_OUTPUT" | grep -c "::" 2>/dev/null || echo "0")
    TOTAL_TESTS=$(echo "$TOTAL_TESTS" | tr -d '\n\r')
    FAILED_TESTS=$(echo "$TEST_OUTPUT" | grep -c "FAILED" 2>/dev/null || echo "0")  
    FAILED_TESTS=$(echo "$FAILED_TESTS" | tr -d '\n\r')
    
    # Ensure we have numeric values
    if ! [[ "$TOTAL_TESTS" =~ ^[0-9]+$ ]]; then
        TOTAL_TESTS=0
    fi
    if ! [[ "$FAILED_TESTS" =~ ^[0-9]+$ ]]; then
        FAILED_TESTS=0
    fi
    
    PASSED_TESTS=$((TOTAL_TESTS - FAILED_TESTS))
    
    # Show clean progress
    if [ $TOTAL_TESTS -gt 0 ]; then
        echo "Running $TOTAL_TESTS tests..."
        echo
        
        # Show test results in a clean format
        IFS=$'\n'
        for line in $(echo "$TEST_OUTPUT" | grep "::"); do
            if echo "$line" | grep -q "FAILED"; then
                echo "[FAIL] $line"
            else
                echo "[PASS] $(echo "$line" | sed 's/::.*/:/')"
            fi
        done
        unset IFS
        
        echo
        echo "=================================================="
        if [ $TEST_RESULT -eq 0 ]; then
            echo "ALL TESTS PASSED! ($PASSED_TESTS/$TOTAL_TESTS) - 100%"
        else
            if [ $TOTAL_TESTS -gt 0 ]; then
                PERCENTAGE=$((PASSED_TESTS * 100 / TOTAL_TESTS))
            else
                PERCENTAGE=0
            fi
            echo "SOME TESTS FAILED! ($PASSED_TESTS/$TOTAL_TESTS) - $PERCENTAGE%"
            echo
            echo "Failed tests:"
            echo "$TEST_OUTPUT" | grep "FAILED" | sed 's/^/   /'
        fi
    else
        echo "No tests found or error running tests"
        echo "$TEST_OUTPUT"
    fi
    
    echo "=================================================="
    echo
    
    if [ $TEST_RESULT -eq 0 ]; then
        echo "$test_type tests completed successfully!"
        return 0
    else
        echo "$test_type tests failed (exit code: $TEST_RESULT)"
        return 1
    fi
}

# Main execution
case "$TEST_TYPE" in
    unit)
        run_unit_tests
        ;;
    integration)
        run_integration_tests  
        ;;
    all)
        echo "Running all tests..."
        run_unit_tests
        unit_result=$?
        cd "$BUILD_DIR"  # Reset to build directory
        run_integration_tests
        integration_result=$?
        
        if [ $unit_result -eq 0 ] && [ $integration_result -eq 0 ]; then
            echo "All test suites completed successfully!"
        else
            echo "Some test suites failed"
            exit 1
        fi
        ;;
    *)
        echo "Unknown test type: $TEST_TYPE"
        exit 1
        ;;
esac

echo "Testing completed!"
