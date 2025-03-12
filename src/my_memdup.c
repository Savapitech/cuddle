/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** my_memdup
*/

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

void *my_memdup(const uint8_t *mem, size_t bytes)
{
    char *result = NULL;

    if (mem == NULL)
        return NULL;
    result = malloc(sizeof(char) * bytes);
    if (result == NULL)
        return NULL;
    for (size_t a = 0; a < bytes; a++) {
        result[a] = mem[a];
    }
    return result;
}
