#include "../include/ThreadPool.h"

ThreadPool::ThreadPool()
{
    for(int i = 0; i < 2; ++i)
    {
        _storage_pool.push_back(std::thread(&ThreadPool::LoopWork, this));
    }
}

ThreadPool::~ThreadPool()
{
    std::lock_guard<std::mutex> guard(MUTEX_STORAGE);
    while(!_storage.empty())
    {
        _storage.front().~unique_ptr();
        _storage.pop();
    }
    for(int i = 0; i < 2; ++i)
    {
        if(_storage_pool[i].joinable())
        {
            _storage_pool[i].join();
        }
    }
}

void ThreadPool::AddTask(std::unique_ptr<Socket> sock_ptr)
{
    if(sock_ptr->IsValid())
    {
        std::lock_guard<std::mutex> guard(MUTEX_STORAGE);
        _storage.push(sock_ptr);
    }
}

void ThreadPool::LoopWork()
{
    while(true)
    {
        if(_storage.empty())
        {
            sleep(2);
            continue;
        }

        std::unique_ptr<ClientSession> ptr_session;
        {
            std::lock_guard<std::mutex> guard(MUTEX_STORAGE);
            //ptr_session = std::make_unique<ClientSession>(std::move(_storage.front().get()));
        }

    }
}