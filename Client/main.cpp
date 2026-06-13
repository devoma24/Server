#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(16000);
    int res = connect(sock, (sockaddr*)&addr, sizeof(addr));
    std::string buffer;
    char answer[2048];
    std::cout << "Ваш запрос серверу: ";
    std::getline(std::cin, buffer);
    while(buffer != "exit")
    {
        std::cout << send(sock, buffer.c_str(), buffer.size(), 0) << std::endl;
        int bytes = recv(sock, answer, 2048, 0);
        std::cout << "Answer: " << std::string(answer, bytes) << std::endl;
        std::cout << "Ваш запрос серверу: ";
        std::getline(std::cin, buffer);
    }
    close(sock);
}