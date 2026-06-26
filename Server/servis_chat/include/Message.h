#pragma once

#include <string>
#include <chrono>

struct Message
{
    std::string _text;
    int _id;
    std::chrono::seconds _current_time;
};