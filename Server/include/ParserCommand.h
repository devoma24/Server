#pragma once

#include "CommandType.h"

#include <sstream>
#include <vector>
#include <iostream>
#include <string>

class ParserCommand
{
    private:
    std::string _key;
    std::vector<std::string> _args;;

    public:
    ParserCommand(std::string&);
    ~ParserCommand() = default;

    public:
    std::string& GetKey();
    std::vector<std::string>& GetArgs();

};