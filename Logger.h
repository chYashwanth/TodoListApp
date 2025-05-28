// Logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>

enum class LogLevel {
    INFO = 0,
    WARNING = 1,
    ERROR = 2
};

class Logger {
private:
    std::ofstream logFile;
    LogLevel minLogLevel = LogLevel::INFO; // Default: show all

    Logger() {
        logFile.open("log.txt", std::ios::app);
        if (!logFile) {
            std::cerr << "[ERROR] Failed to open log file." << std::endl;
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    std::string currentTimestamp() const {
        auto now = std::chrono::system_clock::now();
        auto in_time = std::chrono::system_clock::to_time_t(now);
        std::tm local_tm;
#ifdef _WIN32
        localtime_s(&local_tm, &in_time);
#else
        local_tm = *std::localtime(&in_time);
#endif
        std::stringstream ss;
        ss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }


    std::string logLevelToString(LogLevel level) const {
        switch (level) {
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
        }
    }

public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void setMinLogLevel(LogLevel level) {
        minLogLevel = level;
    }

    void log(const std::string& msg, LogLevel level = LogLevel::INFO) {
        if (level < minLogLevel) return;

        std::string timestampedMsg = "[" + currentTimestamp() + "] [" + logLevelToString(level) + "] " + msg;
        std::cout << timestampedMsg << std::endl;

        if (logFile.is_open()) {
            logFile << timestampedMsg << std::endl;
        }
    }

    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;
};

#endif
