/*
    @author Barney Wilks
*/

#include "Log.hpp"

#include <sstream>
#include <iostream>

using namespace b2m2;

void cLogger::LogMessage(eLevel level, std::string msg)
{
    LogMessage(level, msg, -1, NULL);
}

void cLogger::LogMessage(eLevel level, std::string msg, int line, const char * filename)
{
    if ((int)level & (int) Filter) {
        return;
    }

    std::string text = GetLevelText(level);
    std::stringstream stream;
    stream << "[" << text << "]: ";
    if (line > 0 && filename) {
        stream << "(" << line << ") (" << filename << "): ";
    }

    stream << msg;

    std::cout << stream.str() << std::endl;
}

std::string cLogger::GetLevelText(eLevel level)
{
    switch (level) {
    case eLevel::Error: return "ERROR";
    case eLevel::Fatal: return "FATAL";
    case eLevel::Warning: return "WARNING";
    case eLevel::Infomation: return "INFOMATION";
    case eLevel::None: return "NONE";
    default: return "UNKNOWN";
    }
}
