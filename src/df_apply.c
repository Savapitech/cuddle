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
bool copy_col_values(apply_data_t *d)
{
    size_t sz;

    for (int col = 0; col < d->src->nb_columns; col++) {
        if (col == d->col_idx) {
            d->dst->data[d->row][col] =
                d->apply_func(d->src->data[d->row][col]);
            continue;
        }
        sz = TYPES[d->src->column_type[col]].sz ?
            TYPES[d->src->column_type[col]].sz : strlen(
            (char *)d->src->data[d->row][col]) + 1;
        if (!sz)
            return false;
        d->dst->data[d->row][col] = my_memdup(d->src->data[d->row][col], sz);
        if (d->dst->data[d->row][col] == NULL)
            return false;
    }
    return true;
}

static
dataframe_t *apply_copy_data(dataframe_t *dst, dataframe_t *src,
    void *(*apply_func)(void *vl), int col_idx)
{
    apply_data_t app_dat = { .dst = dst, .src = src, .col_idx = col_idx,
        .apply_func = apply_func };

    for (int row = 0; row < src->nb_rows; row++) {
        dst->data[row] = (void **)malloc(sizeof(void *) *
            src->nb_columns);
        if ((void *)dst->data[row] == NULL)
            return NULL;
        app_dat.row = row;
        if (!copy_col_values(&app_dat))
            return (free((void *)dst->data[row]), NULL);
    }
    dst->nb_rows = src->nb_rows;
    return dst;
}

dataframe_t *df_apply(dataframe_t *df, const char *column,
    void *(*apply_func)(void *vl))
{
    int col_idx;
    dataframe_t *new_df = malloc(sizeof(dataframe_t));

    if (new_df == NULL)
        return NULL;
    if (df == NULL || column == NULL || apply_func == NULL)
        return (free(new_df), NULL);
    col_idx = get_col_idx(df, column);
    if (col_idx < 0)
        return (free(new_df), NULL);
    if (!copy_columns_type(new_df, df) || !copy_columns_name(new_df, df))
        return (free(new_df), NULL);
    new_df->data = (void ***)malloc(sizeof(void *) * df->nb_rows);
    if ((void *)new_df->data == NULL)
        return (free(new_df), NULL);
    new_df->separator = strdup(df->separator);
    if (new_df->separator == NULL)
        return ((free((void *)new_df->data), free(new_df)), NULL);
    new_df->nb_columns = df->nb_columns;
    return apply_copy_data(new_df, df, apply_func, col_idx);
}
