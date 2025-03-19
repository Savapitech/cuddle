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

dataframe_t *df_tail(dataframe_t *df, int nb_rows)
{
    dataframe_t *new_df;
    void ***copy_src_data = df->data;

    if (nb_rows < 0)
        return NULL;
    new_df = malloc(sizeof(dataframe_t));
    if (new_df == NULL)
        return NULL;
    new_df->nb_columns = df->nb_columns;
    df->data += df->nb_rows - nb_rows > 0 ? df->nb_rows - nb_rows : 0;
    if (!copy_columns_type(new_df, df) ||
        !copy_columns_name(new_df, df) ||
        !copy_data(new_df, df, nb_rows))
        return (free(new_df), NULL);
    new_df->separator = strdup(df->separator);
    if (new_df->separator == NULL)
        return (free(new_df), NULL);
    df->data = copy_src_data;
    return new_df;
}
