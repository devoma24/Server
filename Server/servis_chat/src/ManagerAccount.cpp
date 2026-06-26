#include "../include/ManagerAccount.h"

ManagerAccount::ManagerAccount(int Key, std::string Login,
                std::string Password):
    _identification_key(Key), _login(Login), _password(Password) {}

void ManagerAccount::SetName(std::string Name)
{
    std::lock_guard<std::mutex> guard(ACCOUNT);
    _ptrAccount->_name = Name;
}

void ManagerAccount::SetFamily(std::string Family)
{
    std::lock_guard<std::mutex> guard(ACCOUNT);
    _ptrAccount->_family = Family;
}

void ManagerAccount::SetAge(int Age)
{
    std::lock_guard<std::mutex> guard(ACCOUNT);
    _ptrAccount->_family = Age;
}

std::string ManagerAccount::GetName() const
{
    return _ptrAccount->_name;
}

std::string ManagerAccount::GetFamily() const
{
    return _ptrAccount->_family;
}

int ManagerAccount::GetAge() const
{
    return _ptrAccount->_age;
}

int ManagerAccount::GetKey() const
{
    return _identification_key;
}

bool ManagerAccount::CheckLogin(std::string Login) const
{
    return _login == Login;
}

bool ManagerAccount::CheckPassword(std::string Password) const
{
    return _password == Password;
}