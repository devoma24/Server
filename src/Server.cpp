#include "../include/Server.h"

Server::Server()
{
    _worker.Bind();
    _worker.Listen();
    _running = true;
}

Server::~Server()
{
    // for(int i = 0; i < _storage.size(); ++i)
    // {
        // std::unique_ptr<ClientSession> ptr { std::move(_storage.front()) };
        // ptr->Stop_Run();
    // }
    while(!_storage.empty())
    {
        _storage.front()->Stop_Run();
        _storage.pop();
    }
}

void Server::Start()
{
    std::thread thr(&Server::WorkSpace, this);
    std::cout << "Создан поток для просулшивания" << std::endl;
    std::cout << "Введите команду(stop): ";
    std::string word;
    std::cin >> word;
    if(word == "stop")
    {
        this->Stop();
    }
    thr.join();
    std::cout << "Сервер остановлен" << std::endl;
}

void Server::Stop()
{
    _mtx.lock();
    _running = false;
    _worker.Close();
    _mtx.unlock();
}

void Server::WorkSpace()
{
    std::cout << "Start server" << std::endl;
    while(_running)
    {
        Socket client = _worker.Accept();
        if(!client.IsValid())
        {
            break;
        }
        auto ptr = std::make_unique<ClientSession>(std::move(client));
        _storage.push(std::move(ptr));
        std::cout << "Client connected" << std::endl;
    }
}