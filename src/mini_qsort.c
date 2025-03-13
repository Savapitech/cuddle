/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include "dataframe.h"

#include <stddef.h>

static
void mini_swap(void ***a, void ***b)
{
    void **swap = *a;

    *a = *b;
    *b = swap;
}

void mini_qsort(void ***arr, size_t size, int col,
    bool compare(void *, void *))
{
    void **pivot = arr[size - 1];
    size_t cp_index = 0;

    if (size < 2)
        return;
    for (size_t i = 0; i < size - 1; i++) {
        if (!compare(arr[i][col], pivot[col])) {
            mini_swap(&arr[i], &arr[cp_index]);
            cp_index++;
        }
    }
    mini_swap(&arr[cp_index], &arr[size - 1]);
    if (cp_index > 0)
        mini_qsort(arr, cp_index, col, compare);
    if (cp_index + 1 < size)
        mini_qsort(arr + cp_index + 1, size - cp_index - 1, col, compare);
}
