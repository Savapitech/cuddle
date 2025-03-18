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

    if (df == NULL || row > df->nb_rows)
        return NULL;
    col_idx = get_col_idx(df, column);
    if (col_idx < 0)
        return NULL;
    return df->data[row][col_idx];
}
