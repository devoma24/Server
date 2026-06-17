#pragma once

#include "ManagerAccount.h"
#include <vector>
#include <map>

class Chat
{
    private:
    std::vector<std::unique_ptr<ManagerAccount>> _storage_account;
    std::map<int, std::vector<std::string>> _storage_chat;

    public:
    Chat();
    ~Chat();

    public:
    void CreateAccount(ManagerAccount& account);
    bool CheckAccount(const ManagerAccount& account) const;
    bool CheckLogin(std::string) const;
    bool CheckPasswotd(std::string) const;
    bool EditNameAccount(std::string);
    bool EditFamilyAccount(std::string);
    bool EditAgeAccount(int);

    //public:
    //bool SendMessagetoAccount(std::string, int);
    //int FindAccount(std::string, std::string);

};