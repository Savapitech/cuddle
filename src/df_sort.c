/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdlib.h>
#include <string.h>

#include "dataframe.h"
#include "copy_data.h"

static
int get_col_idx(dataframe_t *df, char const *name)
{
    int i = 0;

    if (df == NULL || name == NULL || !df->nb_rows || !df->nb_columns)
        return -1;
    for (; i < df->nb_columns; i++)
        if (strcmp(df->column_names[i], name) == 0)
            return i;
    return -1;
}

dataframe_t *df_sort(dataframe_t *df, char const *column,
    bool (*sort_func)(void *vl1, void *vl2))
{
    dataframe_t *new_df;
    int col_idx = get_col_idx(df, column);

    if (col_idx < 0 || !df->nb_rows || !df->nb_columns)
        return NULL;
    new_df = malloc(sizeof *new_df);
    if (new_df == NULL)
        return NULL;
    new_df->nb_columns = df->nb_columns;
    new_df->nb_rows = df->nb_rows;
    if (!copy_columns_type(new_df, df) || !copy_columns_name(new_df, df) ||
        !copy_data(new_df, df, df->nb_rows))
        return (free(new_df), NULL);
    new_df->separator = strdup(df->separator);
    if (new_df->separator == NULL)
        return (free(new_df), NULL);
    mini_qsort(new_df->data, df->nb_rows, col_idx, sort_func);
    return new_df;
}
