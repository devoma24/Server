#include "Protocol.h"

Packet::Packet(char* buffer, int length)
        : _readPos(0), _buffer(reinterpret_cast<uint8_t*>(buffer),
              reinterpret_cast<uint8_t*>(buffer) + length)
{

}

void Packet::WriteCommand(Command key)
{
    _buffer.push_back(static_cast<uint8_t>(key));
}

void Packet::WriteData(std::string data)
{
    _buffer.push_back(static_cast<uint8_t>(data.size()));
    _buffer.insert(_buffer.end(), data.begin(), data.end());
}

Command Packet::ReadCommand()
{
    return static_cast<Command>(_buffer[_readPos++]);
}

std::string Packet::ReadData()
{
    uint8_t size = _buffer[_readPos++];
    std::string result(_buffer.begin()+ _readPos, _buffer.begin() + _readPos + size);
    _readPos += size;

    return result;
}

const uint8_t* Packet::Data() const
{
    return _buffer.data();
}

size_t Packet::Size() const
{
    return _buffer.size();
}