/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** my_free_array
*/

#include <stdlib.h>
#include <stddef.h>

void my_free_array(char **array)
{
    if (array == NULL)
        return;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}
