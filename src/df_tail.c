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

dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows)
{
    dataframe_t *new_dataframe;
    dataframe_t *cpy_src_df = dataframe;

    if (!nb_rows || nb_rows > dataframe->nb_rows)
        return NULL;
    new_dataframe = malloc(sizeof(dataframe_t));
    if (new_dataframe == NULL)
        return NULL;
    new_dataframe->nb_columns = dataframe->nb_columns;
    new_dataframe->nb_rows = nb_rows;
    dataframe->data += (dataframe->nb_rows - nb_rows);
    if (!copy_columns_type(new_dataframe, dataframe) ||
        !copy_columns_name(new_dataframe, dataframe) ||
        !copy_data(new_dataframe, dataframe, nb_rows))
        return (free(new_dataframe), NULL);
    new_dataframe->separator = strdup(dataframe->separator);
    if (new_dataframe->separator == NULL)
        return (free(new_dataframe), NULL);
    dataframe = cpy_src_df;
    return new_dataframe;
}
