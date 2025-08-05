#include "Logger.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

/**
 * @brief Retrieves the current system time formatted as a string.
 * 
 * @return std::string The current time in "YYYY-MM-DD HH:MM:SS" format.
 */
std::string Logger::getCurrentTime(){
    std::time_t now = std::time(nullptr);                    // Get current time
    char buffer[100];                                        // Buffer to hold formatted time
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now)); // Format time
    return std::string(buffer);                             // Return as string
}

/**
 * @brief Constructs a Logger object and opens the specified log file.
 * 
 * @param filename The name of the log file to create or overwrite.
 * 
 * @details Opens the log file in write mode. If the file cannot be opened,
 *          an error message is displayed to the standard error stream.
 */
Logger::Logger(const std::string& filename) {
    logFile.open(filename, std::ios::out);                  // Open log file in write mode
    if (!logFile) {
        std::cerr << "Error: Unable to open log file: " << filename << std::endl; // Error handling
    }
}

/**
 * @brief Destructor for the Logger class.
 * 
 * @details Closes the log file if it is open.
 */
Logger::~Logger() {
    if (logFile.is_open()) {                                 // Check if log file is open
        logFile.close();                                     // Close the log file
    }
}

/**
 * @brief Logs a message to the log file with a timestamp.
 * 
 * @param message The message to be logged.
 * 
 * @details If the log file is open, the message is written to the file
 *          prefixed with the current timestamp.
 */
void Logger::log(const std::string& message) {
    if (logFile.is_open()) {                                 // Check if log file is open
        logFile << "[" << getCurrentTime() << "] " << message << std::endl; // Write timestamped message
        logFile.flush();                                     // Force write to file immediately
    }
}

void Logger::save(const std::string& message) {
    if (logFile.is_open()) {                                 // Check if log file is open
        logFile << message << std::endl;                     // Write the message to the log file
        logFile.flush();                                     // Force write to file immediately
    } else {
        std::cerr << "Error: Log file is not open." << std::endl; // Error handling if log file is not open
    }
}