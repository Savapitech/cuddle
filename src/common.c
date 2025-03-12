/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdint.h>

#include "dataframe.h"

const types_t TYPES[] = {
    { "BOOL", sizeof(bool) },
    { "INT", sizeof(int) },
    { "UINT", sizeof(uint32_t) },
    { "FLOAT", sizeof(float) },
    { "STRING", 0 }
};
