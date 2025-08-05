#!/bin/bash

set -e

QUIET_MODE=false
if [[ "$1" == "--quiet" || "$1" == "-q" ]]; then
    QUIET_MODE=true
    echo "Quiet mode enabled - suppressing verbose output"
fi

PROJECT_ROOT=$(dirname "$(readlink -f "$0" 2>/dev/null || echo "$0")")
INTEGRATION_TESTS_DIR="$PROJECT_ROOT/integration-tests"
BUILD_DIR="$INTEGRATION_TESTS_DIR/build"

echo "Setting up integration tests for Labyrinth Game project"
echo "Project root directory: $PROJECT_ROOT"
echo "Integration tests directory: $INTEGRATION_TESTS_DIR"

# Set PKG_CONFIG_PATH for macOS Homebrew
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

# Check if integration tests directory exists
if [ ! -d "$INTEGRATION_TESTS_DIR" ]; then
    echo "ERROR: Integration tests directory not found: $INTEGRATION_TESTS_DIR"
    exit 1
fi

# Create build directory
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating integration tests build directory..."
    mkdir -p "$BUILD_DIR"
else
    echo "Using existing integration tests build directory..."
fi

cd "$BUILD_DIR"

# Configure project
echo "Configuring CMake for integration tests..."
cmake ..

# Build
echo "Building integration tests..."
make

# Run tests
echo "Running integration tests..."

if [ -f "./run-integration-tests" ]; then
    echo "Executing integration tests..."
    
    if [ "$QUIET_MODE" = true ]; then
        # Run tests with suppressed verbose output, but show results
        ./run-integration-tests 2>&1 | grep -E "(OK|assertion|FAILED|Error|::)" || {
            echo "WARNING: Integration tests are running with lots of debug output..."
            echo "Please wait for completion (this may take time)..."
            ./run-integration-tests > /dev/null 2>&1
        }
    else
        ./run-integration-tests
    fi
    
    TEST_RESULT=$?
    
    if [ $TEST_RESULT -eq 0 ]; then
        echo "All integration tests passed successfully!"
    else
        echo "Some integration tests failed (exit code: $TEST_RESULT)"
        exit 1
    fi
else
    echo "ERROR: Integration tests executable not found"
    exit 1
fi

echo "Integration testing completed!"
