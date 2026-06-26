#pragma once

#include <iostream>
#include <memory>
#include <mutex>

#include "Account.h"

class ManagerAccount
{
    private:
    std::unique_ptr<Account> _ptrAccount;
    int _identification_key;

    std::string _login;
    std::string _password;

    std::mutex ACCOUNT;

    public:
    ManagerAccount() = default;
    ManagerAccount(int, std::string, std::string);
    ~ManagerAccount() = default;

    public:
    void SetName(std::string);
    void SetFamily(std::string);
    void SetAge(int);
    //void SetLogin();
    //void SetPassword();

    std::string GetName() const;
    std::string GetFamily() const;
    int GetAge() const;
    int GetKey() const;
    bool CheckLogin(std::string) const;
    bool CheckPassword(std::string) const;
};