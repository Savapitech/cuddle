/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdlib.h>
#include <string.h>

#include "copy_data.h"
#include "dataframe.h"

dataframe_t *df_head(dataframe_t *df, int nb_rows)
{
    dataframe_t *new_df;

    if (!nb_rows || nb_rows > df->nb_rows)
        return NULL;
    new_df = malloc(sizeof *new_df);
    if (new_df == NULL)
        return NULL;
    new_df->nb_columns = df->nb_columns;
    new_df->nb_rows = nb_rows;
    if (!copy_columns_type(new_df, df))
        return (free(new_df), NULL);
    if (!copy_columns_name(new_df, df))
        return (free(new_df), NULL);
    if (!copy_data(new_df, df, nb_rows))
        return (free(new_df), NULL);
    return new_df;
}
