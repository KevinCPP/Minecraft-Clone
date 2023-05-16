#include "../include/Utility.h"

#include <iostream>

namespace Utility {
    void warn_message(const std::string& msg) {
        std::clog << "WARNING: " << msg << std::endl;
    }

    void error_message(const std::string& msg) {
        std::cerr << "ERROR: " << msg << std::endl;
    }
    
    void fatal_error_message(const std::string& msg) {
        std::cerr << "FATAL ERROR: " << msg << std::endl;
    }
    
    bool warn(bool condition, const std::string& msg) {
        if(condition) 
            warn_message(msg);
    
        return condition;
    }
    
    bool error(bool condition, const std::string& msg) {
        if(condition)
            error_message(msg);

        return condition;
    }
    
    bool fatal_error(bool condition, const std::string& msg, bool terminate) {
        if(condition) {
            fatal_error_message(msg);

            if(terminate)
                exit(EXIT_FAILURE);
        }

        return condition;
    }
}
