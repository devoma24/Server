#include "../include/Logger.h"

Logger::Logger() {}

Logger::~Logger() {}

void Logger::AddLog(std::string& msg)
{
    _mtx.lock();
    _storage.push_back(msg);
    _mtx.unlock();
}

void Logger::PrintLog()
{
    _mtx.lock();
    for(std::string& msg: _storage)
    {
        std::cout << "LOG: " << msg << std::endl;
    }
    _mtx.unlock();
}

Logger& Logger::Instance()
{
    static Logger _inst;
    return _inst;
}