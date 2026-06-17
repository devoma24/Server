#pragma once

#include <iostream>
#include <memory>

#include "Account.h"

class ManagerAccount
{
    private:
    std::unique_ptr<Account> _ptr_acc;
    int _identification_key;

    std::string _login;
    std::string _password;

    public:
    ManagerAccount();
    ~ManagerAccount();

    public:
    void SetName(std::string);
    void SetFamily(std::string);
    void SetAge(int);
    void SetLogin();
    void SetPassword();

    std::string GetName() const;
    std::string GetFamily() const;
    int GetAge() const;
    int GetKey() const;
    bool CheckLogin(std::string) const;
    bool CheckPassword(std::string) const;
};