
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class Logger {
private:
    std::ofstream logFile;


    std::string getCurrentTime();

public:
    Logger(const std::string& filename);

    ~Logger();

    void log(const std::string& message);
};

#endif // LOGGER_H