#pragma once

#include "ManagerAccount.h"
#include <vector>
#include <iostream>

class DataBaseAccount
{
    private:
    std::vector<std::unique_ptr<ManagerAccount>> _storage;
    std::mutex STORAGE;
    static int _count_key;

    public:
    DataBaseAccount() = default;
    ~DataBaseAccount() = default;
    
    public:
    void AddAccount(std::string, std::string, Account);
    void SetNameFromAccount(int, std::string);
    void SetFamillyFromAccount(int, std::string);
    void SetAgeFromAccount(int, int);
    bool CheckLogin(int, std::string);
    bool CheckPassword(int, std::string);

    public:
    std::string GetName(int);
    std::string GetFamily(int);
    int GetAge(int);

    private:
    int FindAccount(int) const;
};