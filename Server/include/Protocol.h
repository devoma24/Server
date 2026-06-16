#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include "CommandType.h"

class Packet
{
    private:
    size_t _readPos;
    //uint8_t _command;
    //uint32_t _data;
    std::vector<uint8_t> _buffer;

    public:
    Packet(char* buffer, int length);
    Packet() = default;
    ~Packet() = default;

    public:
    void WriteCommand(Command key);
    void WriteData(std::string data);

    public:
    Command ReadCommand();
    std::string ReadData();

    public:
    const uint8_t* Data() const;
    size_t Size() const;
};