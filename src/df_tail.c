/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_tail
*/

#include <stdlib.h>
#include <string.h>

#include "dataframe.h"
#include "copy_data.h"

static
bool copy_data_value_tail(dataframe_t *dst, dataframe_t *src, int row,
    int src_row)
{
    size_t sz;

    for (int col = 0; col < src->nb_columns; col++) {
        sz = TYPES[src->column_type[col]].sz ? TYPES[src->column_type[col]].sz
            : strlen((char *)src->data[src_row][col]) + 1;
        if (!sz)
            return false;
        dst->data[row][col] = my_memdup(src->data[src_row][col], sz);
        if (dst->data[row][col] == NULL)
            return false;
    }
    return true;
}

__attribute__((nonnull(1, 2)))
bool copy_data_tail(dataframe_t *dst, dataframe_t *src, int nb_rows)
{
    int start_row = src->nb_rows - nb_rows;
    int src_row;

    dst->data = (void ***)malloc(sizeof(void *) * nb_rows);
    if ((void *)dst->data == NULL)
        return false;
    for (int row = 0; row < nb_rows; row++) {
        src_row = start_row + row;
        dst->data[row] = (void **)malloc(sizeof(void *) * src->nb_columns);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wanalyzer-malloc-leak"
        if ((void *)dst->data[row] == NULL)
            return (free((void *)dst->data), false);
        if (!copy_data_value_tail(dst, src, row, src_row))
            return (free((void *)dst->data), false);
#pragma GCC diagnostic pop
    }
    return true;
}

dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows)
{
    dataframe_t *new_dataframe;

    if (!nb_rows || nb_rows > dataframe->nb_rows)
        return NULL;
    new_dataframe = malloc(sizeof(dataframe_t));
    if (new_dataframe == NULL)
        return NULL;
    new_dataframe->nb_columns = dataframe->nb_columns;
    new_dataframe->nb_rows = nb_rows;
    if (!copy_columns_type(new_dataframe, dataframe))
        return (free(new_dataframe), NULL);
    if (!copy_columns_name(new_dataframe, dataframe))
        return (free(new_dataframe), NULL);
    if (!copy_data_tail(new_dataframe, dataframe, nb_rows))
        return (free(new_dataframe), NULL);
    return new_dataframe;
}
