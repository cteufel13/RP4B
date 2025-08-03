#include <logger.hpp>
#include <chrono>
#include <filesystem>
#include <iostream>

Logger &Logger::getInstance()
{
    static Logger instance;
    return instance;
};
void Logger::set_log_file(const std::string &file_path)
{
    std::filesystem::path full_path = std::filesystem::current_path() / file_path;
    std::lock_guard<std::mutex> lock(log_mutx);

    if (file.is_open())
    {
        file.close(); // Close any previously open file
    }

    file.open(full_path, std::ios::app);

    if (!file.is_open())
    {
        std::cerr << "[Logger] Failed to open log file: " << full_path << std::endl;
    }
}

Logger::~Logger()
{
    if (file.is_open())
    {
        file.close();
    }
}

void Logger::log(LogLevel level, const std::string message)
{
    std::lock_guard<std::mutex> lock(log_mutx); // Locks mutex so only one log at time
    std::ostringstream oss;
    oss << "[" << currentDateTime() << "]" << "[" << levelToString(level) << "]" << message << std::endl; // Log Message

    std::string output = oss.str();

    if (file.is_open()) // Prints to File
    {
        file << output;
        file.flush();
    };
};

void Logger::debug(const std::string &message) { log(LogLevel::DEBUG, message); }
void Logger::info(const std::string &message) { log(LogLevel::INFO, message); };
void Logger::warning(const std::string &message) { log(LogLevel::WARNING, message); };
void Logger::error(const std::string &message) { log(LogLevel::ERROR, message); };

std::string Logger::levelToString(LogLevel level)
{
    switch (level)
    {
    case LogLevel::DEBUG:
        return "DEBUG";
    case LogLevel::INFO:
        return "INFO";
    case LogLevel::ERROR:
        return "ERROR";
    case LogLevel::WARNING:
        return "WARNING";
    }
};

std::string Logger::currentDateTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm;
    localtime_r(&time_now, &local_tm);

    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
};