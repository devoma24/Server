#include "../include/DataBaseAccount.h"

void DataBaseAccount::AddAccount(std::string Login, std::string Password,
                            Account Data)
{
    std::lock_guard<std::mutex> guard(STORAGE);
    auto ptr = std::make_unique<ManagerAccount>(_count_key++, Login, Password);
    ptr->SetName(Data._name);
    ptr->SetFamily(Data._family);
    ptr->SetAge(Data._age);
    _storage.push_back(std::move(ptr));
}

void DataBaseAccount::SetNameFromAccount(int Id, std::string Name)
{
    std::lock_guard<std::mutex> guard(STORAGE);
    int index = FindAccount(Id);
    _storage[Id]->SetName(Name);
}

void DataBaseAccount::SetFamillyFromAccount(int Id, std::string Family)
{
    std::lock_guard<std::mutex> guard(STORAGE);
    int index = FindAccount(Id);
    _storage[Id]->SetFamily(Family);
}

void DataBaseAccount::SetAgeFromAccount(int Id, int Age)
{
    std::lock_guard<std::mutex> guard(STORAGE);
    int index = FindAccount(Id);
    _storage[Id]->SetAge(Age);
}

bool DataBaseAccount::CheckLogin(int Id, std::string Login)
{
    std::lock_guard<std::mutex> guard(STORAGE);
    int index = FindAccount(Id);
    return _storage[Id]->CheckLogin(Login);;
}

bool DataBaseAccount::CheckPassword(int Id, std::string Password)
{
    std::lock_guard<std::mutex> guard(STORAGE);
    int index = FindAccount(Id);
    return _storage[Id]->CheckPassword(Password);
}

std::string DataBaseAccount::GetName(int Id)
{
    std::lock_guard<std::mutex> guard(STORAGE);
    int index = FindAccount(Id);
    return _storage[Id]->GetName();
}

std::string DataBaseAccount::GetFamily(int Id)
{
    std::lock_guard<std::mutex> guard(STORAGE);
    int index = FindAccount(Id);
    return _storage[Id]->GetFamily();
}

int DataBaseAccount::GetAge(int Id)
{
    std::lock_guard<std::mutex> guard(STORAGE);
    int index = FindAccount(Id);
    return _storage[Id]->GetAge();
}

int DataBaseAccount::FindAccount(int id) const
{
    for(int i = 0; i < _storage.size(); ++i)
    {
        if(_storage[0]->GetKey() == id)
        {
            return i;
        }
    }
}