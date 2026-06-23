#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <memory>
#include <queue>
#include <vector>

#include "../include/ClientSession.h"

class ThreadPool
{
    private:
    std::queue<std::unique_ptr<Socket>> _storage;
    std::vector<std::thread> _storage_pool;
    std::mutex MUTEX_STORAGE;

    public:
    ThreadPool();
    ~ThreadPool();

    public:
    void AddTask(std::unique_ptr<Socket>);

    private:
    void LoopWork();
};