#pragma once

#include <cstdint>

enum class Command : uint8_t
{
    AUTHORIZATION = 0,
    FIND_FRIEND,
    SEND_MESSAGE,
    LIST_FRIEND,
    ADD_FRIEND,
    LIST_CHATS,
    OPEN_CHAT,
    MAIN
};