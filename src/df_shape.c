/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include "dataframe.h"

dataframe_shape_t df_shape(dataframe_t *df)
{
    return (dataframe_shape_t){ df->nb_rows, df->nb_columns };
}
