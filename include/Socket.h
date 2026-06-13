#pragma once

#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

const int INVALID = -1;

class Socket
{
    private:
    int _sockfd;
    sockaddr_in _sockaddr;

    private:
    int Send(const char* buffer, size_t length);
    int Receive(char* buffer, size_t length);

    public:
    Socket();
    Socket(int &&sock);
    Socket(Socket&& sock);
    ~Socket();

    Socket(Socket&) = delete;
    Socket operator =(Socket&) = delete;

    public:
    void Bind(int port = 16000);
    void Listen(int backlog = 3);
    Socket Accept();

    void SendAll(const char* buffer, size_t length);
    std::string ReceiveData();

    public:
    void Close();
    bool IsValid();
};