/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include "dataframe.h"

void df_free(dataframe_t *df)
{
    if (df == NULL)
        return;
    for (int row = 0; row < df->nb_rows; row++) {
        for (int col = 0; col < df->nb_columns; col++)
            free(df->data[row][col]);
        free((void *)df->data[row]);
    }
    free((void *)df->data);
    free(df->column_type);
    for (int i = 0; i < df->nb_columns; i++)
        free(df->column_names[i]);
    free((void *)df->column_names);
    free(df->separator);
    free(df);
}
