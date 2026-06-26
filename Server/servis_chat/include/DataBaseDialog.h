#pragma once

#include "Dialogue.h"

#include <mutex>
#include <memory>
#include <iostream>

class DataBase
{
    private:
    std::vector<Dialogue> _storage;
    std::mutex STORAGE;
    
    public:
    DataBase() = default;
    ~DataBase() = default;
    DataBase(DataBase&) = delete;
    DataBase& operator=(DataBase&) = delete;

    public:
    void AddDialog(int id);
    void AddMessage(int id, Message message);
    std::vector<Message>* GetDialog(int id);

    private:
    std::shared_ptr<Dialogue> FindDialog(int id) const;
};