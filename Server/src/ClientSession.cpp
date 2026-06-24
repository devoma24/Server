#include "../include/ClientSession.h"

ClientSession::ClientSession(Socket&& sock): 
        _worker(std::move(sock)) {}

ClientSession::~ClientSession()
{
    std::cout << "Сессия закрыта" << std::endl;
}

// void ClientSession::Stop_Run()
// {
//     _MTX.lock();
//     _running = false;
//     _worker.Close();
//     _MTX.unlock();
// }

void ClientSession::Run()
{
    std::cout << "Start session run" << std::endl;
    while (_worker.IsValid())
    {
        this->recvData();
        std::cout << "Сообщение от клиента: " << _buffer << std::endl;
        // this->sendData();
        this->requestProcessing();
    }
    std::cout << "Выход из run" << std::endl;
}

void ClientSession::recvData()
{
    try
    {
        _buffer = _worker.ReceiveData();
        if(_buffer == "Error")
        {
            std::cout << "Ошибка при отправке данных" << std::endl;
            std::cout << "Продолжаем работу" << std::endl;
        }
        if(_buffer == "Disconnected")
        {
            std::cout << "Соединение с клиентом закрыто" << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void ClientSession::sendData()
{
    _worker.SendAll(static_cast<char*>(_buffer.data()), _buffer.size());
}

void ClientSession::requestProcessing()
{
    //ParserCommand pcmd { _buffer };
    Packet packet { _buffer.data(), _buffer.size() };
    
    switch (packet.ReadCommand())
    {
    case Command::ADD:
    {
        std::string key = packet.ReadData();
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
        break;
    }
    case Command::GET:
    {
        std::string key = packet.ReadData();
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
        break;
    }   
    case Command::SET:
    {
        std::string key = packet.ReadData();
        if(STORAGE.count(key) != 0)
        {
            STORAGE[key] = std::stoi(packet.ReadData());
            _buffer.clear();
            _buffer = "Успешная операция изменения";
        }
        else
        {
            _buffer.clear();
            _buffer = "Ошибка при изменении данных";
        }
        this->sendData();
        break;
    } 
    case Command::DELETE:
    {
        std::string key = packet.ReadData();
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
        break;
    }
    default:
    {
        _buffer.clear();
        _buffer = "Некорректная команда";
        std::cout << _buffer << std::endl;
        this->sendData();
        break;
    }
    }
}