/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef COPY_DATA
    #define COPY_DATA
    #include <stdbool.h>

    #include "dataframe.h"

bool copy_columns_type(dataframe_t *dst, dataframe_t *src);
bool copy_columns_name(dataframe_t *dst, dataframe_t *src);
bool copy_data(dataframe_t *dst, dataframe_t *src, int nb_rows);
#endif
