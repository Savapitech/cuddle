/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdlib.h>
#include <string.h>

#include "dataframe.h"

__attribute__((nonnull))
bool copy_columns_type(dataframe_t *dst, dataframe_t *src)
{
    dst->column_type = malloc(sizeof(column_type_t) * src->nb_columns);
    if (dst->column_type == NULL)
        return false;
    for (int i = 0; i < src->nb_columns; i++)
        dst->column_type[i] = src->column_type[i];
    return true;
}

__attribute__((nonnull))
bool copy_columns_name(dataframe_t *dst, dataframe_t *src)
{
    dst->column_names = (char **)malloc(sizeof(char *) * src->nb_columns);
    if ((void *)dst->column_names == NULL)
        return false;
    for (int i = 0; i < src->nb_columns; i++) {
        dst->column_names[i] = strdup(src->column_names[i]);
        if (dst->column_names[i] == NULL)
            return false;
    }
    return true;
}

static
bool copy_data_value(dataframe_t *dst, dataframe_t *src, int row)
{
    size_t sz;

    for (int col = 0; col < src->nb_columns; col++) {
        sz = TYPES[src->column_type[col]].sz ? TYPES[src->column_type[col]].sz
            : strlen((char *)src->data[row][col]) + 1;
        if (!sz)
            return false;
        dst->data[row][col] = my_memdup(src->data[row][col], sz);
        if (dst->data[row][col] == NULL)
            return false;
    }
    return true;
}

__attribute__((nonnull(1, 2)))
bool copy_data(dataframe_t *dst, dataframe_t *src, int nb_rows)
{
    int row = 0;

    dst->data = (void ***)malloc(sizeof(void *) * nb_rows);
    if ((void *)dst->data == NULL)
        return false;
    for (; row < nb_rows && row < src->nb_rows; row++) {
        dst->data[row] = (void **)malloc(sizeof(void *) * src->nb_columns);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wanalyzer-malloc-leak"
        if ((void *)dst->data[row] == NULL)
            return (free((void *)dst->data), false);
        if (!copy_data_value(dst, src, row))
            return (free((void *)dst->data), false);
#pragma GCC diagnostic pop
    }
    dst->nb_rows = row;
    return true;
}
