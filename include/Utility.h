#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>


namespace Utility {
    void log_message(const std::string& msg);
    void warn_message(const std::string& msg);
    void error_message(const std::string& msg);
    void fatal_error_message(const std::string& msg);

    bool log(bool condition, const std::string& msg);
    bool warn(bool condition, const std::string& msg);
    bool error(bool condition, const std::string& msg);
    bool fatal_error(bool condition, const std::string& msg, bool terminate = false);

}

#endif
