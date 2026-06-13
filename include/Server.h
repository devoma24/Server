#pragma once

#include "ClientSession.h"
#include <memory>
#include <queue>

class Server
{
    private:
    Socket _worker;
    std::atomic<bool> _running;
    std::queue<std::unique_ptr<ClientSession>> _storage;
    std::mutex _mtx;

    public:
    Server();
    ~Server();

    public:
    void Start();
    void Stop();
    void WorkSpace();
};