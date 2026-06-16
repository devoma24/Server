#pragma once

#include <string>
#include <vector>
#include <mutex>
#include <iostream>

#define LOG(msg) Logger::Instance().AddLog(msg)

class Logger
{
    private:
    static std::vector<std::string> _storage;
    std::mutex _mtx;

    public:
    Logger();
    ~Logger();

    public:
    void AddLog(std::string&);
    void PrintLog();
    Logger& Instance();
};