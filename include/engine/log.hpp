#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

namespace engine {
    enum class LogLevel {
        Debug,
        Info,
        Warning,
        Error
    };

    class Logger {
    private:
        std::string name_;
        std::ostream* output_;
        LogLevel level_;

    public:
        explicit Logger(std::string_view name = "", LogLevel minLevel = LogLevel::Error, std::ostream& stream = std::clog) : name_(name), output_(&stream), level_(minLevel) {}

        void set_name(std::string_view name) {
            name_ = name;
        }

        void set_output(std::ostream& stream) {
            output_ = &stream;
        }

        void set_level(LogLevel level) {
            level_ = level;
        }

        void log(LogLevel level, std::string_view message) const {
            if(level < level_) return;
            const char* label = "UNKNOWN";
            switch(level) {
                case LogLevel::Debug: label = "DEBUG"; break;
                case LogLevel::Info: label = "INFO"; break;
                case LogLevel::Warning: label = "WARN"; break;
                case LogLevel::Error: label = "ERROR"; break;
            }
            *output_ << "[" << name_ << "][" << label << "] " << message << std::endl;
        }

        void debug(std::string_view message) const {
            log(LogLevel::Debug, message);
        }

        void info(std::string_view message) const {
            log(LogLevel::Info, message);
        }

        void warning(std::string_view message) const {
            log(LogLevel::Warning, message);
        }

        void error(std::string_view message) const {
            log(LogLevel::Error, message);
        }

        void critical(std::string_view message) const {
            log(LogLevel::Error, message);
            throw std::runtime_error(std::string(message));
        }
    };
}

#endif
