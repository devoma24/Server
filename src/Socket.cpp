#include "../include/Socket.h"

Socket::Socket()
{
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(_sockfd == INVALID)
    {
        std::cout << "Неудачное создание сокета" << std::endl;
        exit(0);
    }
}

Socket::Socket(int &&sock): _sockfd(std::move(sock)) {}

Socket::Socket(Socket&& sockaa)
{
    _sockfd = std::move(sockaa._sockfd);
    _sockaddr = std::move(sockaa._sockaddr);
    sockaa._sockfd = INVALID;
}

Socket::~Socket()
{
    if(_sockfd != INVALID)
    {
        close(_sockfd);
    }
    std::cout << "Сокет уничтожен" << std::endl;
}

void Socket::Bind(int port)
{
    _sockaddr.sin_family = AF_INET;
    _sockaddr.sin_port = htons(port);
    _sockaddr.sin_addr.s_addr = INADDR_ANY;   
    if(bind(_sockfd, (sockaddr*)&_sockaddr, sizeof(_sockaddr)) == INVALID)
    {
        std::cout << "Неудачная привязка порта" << std::endl;
    }
}

void Socket::Listen(int backlog)
{
    if(listen(_sockfd, backlog) == INVALID)
    {
        std::cout << "Ошибка при вызове listen" << std::endl;
    }
}

Socket Socket::Accept()
{
    return Socket(accept(_sockfd, nullptr, nullptr));
}

int Socket::Send(const char* buffer, size_t length)
{
    return send(_sockfd, buffer, length, 0);
}

int Socket::Receive(char* buffer, size_t length)
{
    return recv(_sockfd, buffer, length, 0);
}

void Socket::SendAll(const char* buffer, size_t length)
{
    int total_bytes = 0;
    while(total_bytes < length)
    {
        int send_bytes = Send(buffer + total_bytes, length - total_bytes);
        if(send_bytes == 0 || send_bytes == 0)
        {
            throw std::runtime_error("Ошибка отправки данных");
        }
        total_bytes += send_bytes;
    }
}

std::string Socket::ReceiveData() 
{
    char buffer[2048];
    int bytes = this->Receive(buffer, sizeof(buffer));
    if(bytes == -1)
    {
        return std::string("Error");
    }
    if(bytes == 0)
    {
        return std::string("Disconnected");
    }
    return std::string(buffer, bytes);
}

void Socket::Close()
{
    if(_sockfd != INVALID)
    {
        shutdown(_sockfd, SHUT_RDWR);
        close(_sockfd);
        _sockfd = INVALID;
    }
}

bool Socket::IsValid()
{
    return _sockfd != INVALID;
}