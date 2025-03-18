/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdint.h>

#include "dataframe.h"

const types_t TYPES[] = {
    { "bool", 0 },
    { "int", sizeof(int) },
    { "unsigned int", sizeof(uint32_t) },
    { "float", sizeof(float) },
    { "string", 0 }
};
