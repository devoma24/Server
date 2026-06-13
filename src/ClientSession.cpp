#include "../include/ClientSession.h"

ClientSession::ClientSession(Socket&& sock): 
        _worker(std::move(sock)), _running(true)
{
    _thr = std::thread(&ClientSession::run, this);
}

ClientSession::~ClientSession()
{
    if(_thr.joinable())
    {
        _thr.join();
    }
    std::cout << "Сессия закрыта" << std::endl;
}

void ClientSession::Stop_Run()
{
    _MTX.lock();
    _running = false;
    _worker.Close();
    _MTX.unlock();
}

void ClientSession::run()
{
    std::cout << "Start session run" << std::endl;
    while (_running && _worker.IsValid())
    {
        this->recvData();
        std::cout << "Сообщение от клиента: " << _buffer << std::endl;
        // this->sendData();
        this->requestProcessing();
        sleep(2);
    }
    std::cout << "Выход из run" << std::endl;
}

void ClientSession::recvData()
{
    _buffer = _worker.ReceiveData();
    if(_buffer == "Error" || _buffer == "Disconnected")
    {
        std::cout << "Закрыто соединение с клиентом" << std::endl;
        this->Stop_Run();
    }
}

void ClientSession::sendData()
{
    _worker.SendAll(static_cast<char*>(_buffer.data()), _buffer.size());
}

void ClientSession::requestProcessing()
{
    ParserCommand pcmd { _buffer };
    
    if(pcmd.GetKey() == "GET")
    {
        _MTX.lock();
        std::string key = pcmd.GetArgs()[0];
        if(STORAGE.count(key) != 0)
        {
            _buffer.clear();
            int count = STORAGE.at(key);
            _buffer = key + ": " + std::to_string(count);
            std::cout << "Count = " << count << std::endl;
        }
        else
        {
            _buffer.clear();
            _buffer = "Нет такого товара в каталоге";
        }
        this->sendData();
        _MTX.unlock();
    }
    else if(pcmd.GetKey() == "SET")
    {
        _MTX.lock();
        std::string key = pcmd.GetArgs()[0];
        if(STORAGE.count(key) != 0)
        {
            STORAGE[key] = std::stoi(pcmd.GetArgs()[1]);
            _buffer.clear();
            _buffer = "Успешная операция изменения";
        }
        else
        {
            _buffer.clear();
            _buffer = "Ошибка при изменении данных";
        }
        this->sendData();
        _MTX.unlock();
    }
    else if(pcmd.GetKey() == "ADD")
    {
        _MTX.lock();
        std::string key = pcmd.GetArgs()[0];
        if(STORAGE.count(key) == 0)
        {
            STORAGE.insert_or_assign(key, 0);
            _buffer.clear();
            _buffer = "Успешная операция добавления";
        }
        else
        {
            _buffer.clear();
            _buffer = "Ошибка при добавлении данных - товар уже существует";
        }
        this->sendData();
        _MTX.unlock();
    }
    else if(pcmd.GetKey() == "DELETE")
    {
        _MTX.lock();
        std::string key = pcmd.GetArgs()[0];
        if(STORAGE.count(key) != 0)
        {
            STORAGE.erase(key);
            _buffer.clear();
            _buffer = "Успешная операция удаления";
        }
        else
        {
            _buffer.clear();
            _buffer = "Ошибка при удаление ключа";
        }
        this->sendData();
        _MTX.unlock();
    }
}