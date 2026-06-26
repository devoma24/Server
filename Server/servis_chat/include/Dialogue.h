#pragma once

#include <vector>
#include "Message.h"

struct Dialogue
{
    int _id_sum;
    std::vector<Message> _storage;
};
