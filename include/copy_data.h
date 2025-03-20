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

typedef struct {
    dataframe_t *dst;
    dataframe_t *src;
    int col_idx;
    int row;
    void *(*apply_func)(void *vl);
} apply_data_t;

typedef struct {
    dataframe_t *dst;
    dataframe_t *src;
    int col_idx;
    int row;
    column_type_t downcast;
} type_data_t;

bool copy_columns_type(dataframe_t *dst, dataframe_t *src);
bool copy_columns_name(dataframe_t *dst, dataframe_t *src);
bool copy_data(dataframe_t *dst, dataframe_t *src, int nb_rows);
bool copy_data_value(dataframe_t *dst, dataframe_t *src, int dst_row,
    int src_row);
#endif
