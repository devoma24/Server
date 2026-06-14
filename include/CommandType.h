#pragma once

#include <cstdint>

enum class Command: uint8_t
{
    ADD = 0,
    GET = 1,
    SET = 2,
    DELETE = 3
};