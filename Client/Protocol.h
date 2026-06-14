#pragma once

#include <string>
#include <vector>
#include <cstdint>

enum class Command: uint8_t
{
    ADD = 0,
    GET = 1,
    SET = 2,
    DELETE = 3
};

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

    private:
    Command ReadCommand();
    std::string ReadData();
};