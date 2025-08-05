#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <iostream>

// Include test suites
#include "CellTest.h"
#include "PlayerTest.h"
#include "LabyrinthTest.h"

int main() {
    // Create the event manager and test controller
    CPPUNIT_NS::TestResult controller;

    // Add a listener that collects test results
    CPPUNIT_NS::TestResultCollector result;
    controller.addListener(&result);

    // Add a listener that prints dots as tests run
    CPPUNIT_NS::BriefTestProgressListener progress;
    controller.addListener(&progress);

    // Add the top suite to the test runner
    CPPUNIT_NS::TestRunner runner;
    runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
    runner.run(controller);

    // Print test results
    if (result.wasSuccessful()) {
        std::cout << "\nAll tests passed!" << std::endl;
        return 0;
    } else {
        std::cout << "\nSome tests failed:" << std::endl;
        return 1;
    }
}
