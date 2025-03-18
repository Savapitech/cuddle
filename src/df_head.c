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

    if (!nb_rows)
        return NULL;
    new_df = malloc(sizeof *new_df);
    if (new_df == NULL)
        return NULL;
    new_df->nb_columns = df->nb_columns;
    if (!copy_columns_type(new_df, df) || !copy_columns_name(new_df, df) ||
        !copy_data(new_df, df, nb_rows))
        return (free(new_df), NULL);
    new_df->separator = strdup(df->separator);
    if (new_df->separator == NULL)
        return (free(new_df), NULL);
    return new_df;
}
