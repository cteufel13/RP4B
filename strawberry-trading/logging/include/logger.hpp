#pragma once
#include <fstream>
#include <string>
#include <mutex>

enum class LogLevel
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
};

class Logger
{
public:
    static Logger &getInstance();
    void set_log_file(const std::string &file_path);

    void log(LogLevel level, const std::string message);

    void debug(const std::string &message);
    void info(const std::string &message);
    void warning(const std::string &message);
    void error(const std::string &message);

private:
    Logger() = default;
    ~Logger();
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    std::ofstream file;
    std::mutex log_mutx;

    std::string levelToString(LogLevel level);
    std::string currentDateTime();
};