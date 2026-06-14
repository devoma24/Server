#pragma once

#include "Socket.h"
//#include "ParserCommand.h"
#include "Protocol.h"

#include <thread>
#include <mutex>
#include <atomic>
#include <string>
#include <map>

static std::map<std::string, int> STORAGE;

class ClientSession
{
    private:
    Socket _worker;
    std::thread _thr;
    std::atomic<bool> _running;
    std::string _buffer;
    std::mutex _MTX;

    public:
    ClientSession(Socket&&);
    ~ClientSession();

    public:
    void Stop_Run();

    private:
    void run();

    private:
    void recvData();
    void sendData();
    void requestProcessing();
};