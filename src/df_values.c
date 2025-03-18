/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include "dataframe.h"
#include "utils.h"

void *df_get_value(dataframe_t *df, int row, char const *column)
{
    int col_idx;

    if (df == NULL || column == NULL || row > df->nb_rows)
        return NULL;
    col_idx = get_col_idx(df, column);
    if (col_idx < 0)
        return NULL;
    return df->data[row][col_idx];
}

void **df_get_values(dataframe_t *df, char const *column)
{
    int col_idx;
    void **result;

    if (df == NULL || column == NULL)
        return NULL;
    col_idx = get_col_idx(df, column);
    if (col_idx < 0)
        return NULL;
    result = (void **)malloc(sizeof(void *) * df->nb_rows);
    if ((void *)result == NULL)
        return NULL;
    for (int i = 0; i < df->nb_rows; i++)
        result[i] = df->data[i][col_idx];
    return result;
}
