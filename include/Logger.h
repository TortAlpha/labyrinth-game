#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

/**
 * @brief The Logger class provides functionality to log messages to a file with timestamps.
 * 
 * @details 
 * This class handles the creation and management of a log file. It allows logging messages with 
 * the current timestamp, facilitating the tracking of events and actions within the game.
 * 
 * Author: Roman Avanesov
 * Created: 25.12.2024
 * Last Modified: 30.12.2024
 */
class Logger {
    private:
        std::ofstream logFile;      ///< Output file stream for the log file.

        /**
         * @brief Retrieves the current system time formatted as a string.
         * 
         * @return std::string The current time in "YYYY-MM-DD HH:MM:SS" format.
         */
        std::string getCurrentTime();

    public:
        /**
         * @brief Constructs a Logger object and opens the specified log file.
         * 
         * @param filename The name of the log file to create or append to.
         * 
         * @throws std::ios_base::failure If the log file cannot be opened.
         */
        Logger(const std::string& filename);

        /**
         * @brief Destructor for the Logger class.
         * 
         * @details Closes the log file if it is open.
         */
        ~Logger();

        /**
         * @brief Logs a message to the log file with a timestamp.
         * 
         * @param message The message to be logged.
         */
        void log(const std::string& message);

        /**
         * @brief Logs a message to the log file without a timestamp.
         * 
         * @param message The message to be logged.
         */
        void save(const std::string& message);

};

#endif // LOGGER_H