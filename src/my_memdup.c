/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** my_memdup
*/

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void *my_memdup(const uint8_t *mem, size_t bytes)
{
    char *result = NULL;

    if (mem == NULL)
        return NULL;
    result = malloc(sizeof(char) * bytes);
    if (result == NULL)
        return NULL;
    memcpy(result, mem, bytes);
    return result;
}
