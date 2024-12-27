#include "Logger.h"

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>


std::string Logger::getCurrentTime(){
		std::time_t now = std::time(nullptr);
		char buffer[100];
		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
		return std::string(buffer);
	}

Logger::Logger(const std::string& filename) {
	logFile.open(filename, std::ios::out);
	if (!logFile) {
		std::cerr << "Error: Unable to open log file: " << filename << std::endl;
	}
}

Logger::~Logger() {
	if (logFile.is_open()) {
		logFile.close();
	}
}

void Logger::log(const std::string& message) {
	if (logFile.is_open()) {
		logFile << "[" << getCurrentTime() << "] " << message << std::endl;
	}
}