/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <string.h>

#include "dataframe.h"
#include "copy_data.h"
#include "utils.h"

static
bool handle_rows_cap(dataframe_t *df, int *cap, int sz)
{
    void ***new_ptr;

    if (sz < *cap)
        return true;
    new_ptr = (void ***)realloc((void *)df->data,
        sizeof *df->data * *cap << 1);
    if ((void *)new_ptr == NULL)
        return false;
    df->data = new_ptr;
    *cap <<= 1;
    return true;
}

static
dataframe_t *filter_copy_data(dataframe_t *dst, dataframe_t *src,
    bool (*filter_func)(void *vl), int col_idx)
{
    int copied_rows = 0;
    int rows_cap = 1;

    for (int row = 0; row < src->nb_rows; row++) {
        if (!filter_func(src->data[row][col_idx]))
            continue;
        if (!handle_rows_cap(dst, &rows_cap, copied_rows))
            return NULL;
        dst->data[copied_rows] = (void **)malloc(sizeof(void *) *
            src->nb_columns);
        if ((void *)dst->data[copied_rows] == NULL)
            return NULL;
        if (!copy_data_value(dst, src, copied_rows, row))
            return (free((void *)dst->data[copied_rows]), NULL);
        copied_rows++;
    }
    dst->nb_rows = copied_rows;
    return dst;
}

dataframe_t *df_filter(dataframe_t *df, const char *column,
    bool (*filter_func)(void *vl))
{
    int col_idx;
    dataframe_t *new_df = malloc(sizeof(dataframe_t));

    if (new_df == NULL)
        return NULL;
    if (df == NULL || column == NULL || filter_func == NULL)
        return (free(new_df), NULL);
    col_idx = get_col_idx(df, column);
    if (col_idx < 0)
        return (free(new_df), NULL);
    if (!copy_columns_type(new_df, df) || !copy_columns_name(new_df, df))
        return (free(new_df), NULL);
    new_df->data = (void ***)malloc(sizeof(void *));
    if ((void *)new_df->data == NULL)
        return (free(new_df), NULL);
    new_df->separator = strdup(df->separator);
    if (new_df->separator == NULL)
        return ((free((void *)new_df->data), free(new_df)), NULL);
    new_df->nb_columns = df->nb_columns;
    return filter_copy_data(new_df, df, filter_func, col_idx);
}
