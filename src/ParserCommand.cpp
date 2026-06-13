#include "../include/ParserCommand.h"

ParserCommand::ParserCommand(std::string& query)
{
    std::istringstream ist(query);
    std::string word;
    ist >> _key;
    while(ist.good() && !ist.eof())
    {
        ist >> word;
        _args.push_back(word);
        word.clear();
    }
}

std::string& ParserCommand::GetKey()
{
    return _key;
}

std::vector<std::string>& ParserCommand::GetArgs()
{
    return _args;
}