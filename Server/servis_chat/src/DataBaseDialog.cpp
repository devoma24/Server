#include "../include/DataBaseDialog.h"

void DataBase::AddDialog(int id)
{
    std::lock_guard<std::mutex> guard(STORAGE);
    _storage.push_back(Dialogue{ id });
}

void DataBase::AddMessage(int id, Message message)
{
    std::lock_guard<std::mutex> guard(STORAGE);
    auto ptr = FindDialog(id);
    ptr->_storage.push_back(message);
}

std::shared_ptr<Dialogue> DataBase::FindDialog(int id) const
{
    for(const auto dialog: _storage)
    {
        if(dialog._id_sum == id)
        {
            return std::make_shared<Dialogue>(&dialog);
        }
    }
    std::cout << "Ошибка при добавлении. Диалог еще не создан" << std::endl;
}