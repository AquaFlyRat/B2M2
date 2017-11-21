/*
    @author Barney Wilks
*/

#pragma once

#include <string>
#include "../Common.hpp"

#define B2M2_LOG(level, msg) \
    cLogger::Get()->LogMessage(level, msg, __LINE__, __FILE__)

namespace arch {
    class cLogger {
    public:
        enum class eLevel {
            Fatal = 1, 
            Error = 2, 
            Warning = 4, 
            Infomation = 8, 
            None = 16
        };

        static cLogger* Get() { static cLogger logger; return &logger; }

        void LogMessage(eLevel level, std::string msg);
        void LogMessage(eLevel level, std::string msg, int line, const char *filename);

        eLevel Filter = eLevel::None;

    private:
        std::string GetLevelText(eLevel level);

    };
}
