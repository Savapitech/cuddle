/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <limits.h>
#include <math.h>
#include <stdio.h>

#include "dataframe.h"

static
void std_calc(void *vl, df_describe_t *des, column_type_t type)
{
    switch (type) {
        case INT:
            des->std += pow(*(int *)vl - des->mean, 2);
            break;
        case UINT:
            des->std += pow(*(uint32_t *)vl - des->mean, 2);
            break;
        case FLOAT:
            des->std += pow(*(float *)vl - des->mean, 2);
        default:
            break;
    }
}

static
void value_calc(void *vl, df_describe_t *des, column_type_t type)
{
    switch (type) {
        case INT:
            des->mean += *(int *)vl;
            des->max = *(int *)vl > (int)des->max ? *(int *)vl : des->max;
            des->min = *(int *)vl < (int)des->min ? *(int *)vl : des->min;
            break;
        case UINT:
            des->mean += *(uint32_t *)vl;
            des->max = *(uint32_t *)vl > des->max ? *(uint32_t *)vl : des->max;
            des->min = *(uint32_t *)vl < des->min ? *(uint32_t *)vl : des->min;
            break;
        case FLOAT:
            des->mean += *(float *)vl;
            des->max = *(float *)vl > des->max ? *(float *)vl : des->max;
            des->min = *(float *)vl < des->min ? *(float *)vl : des->min;
        default:
            break;
    }
}

void df_describe(dataframe_t *df)
{
    df_describe_t df_des = { 0, .min = (float)0xffffffffffffffff };

    if (df == NULL || !df->nb_rows || !df->nb_columns)
        return;
    for (int col = 0; col < df->nb_columns; col++) {
        if (df->column_type[col] > FLOAT || !df->column_type[col])
            continue;
        df_des = (df_describe_t){ 0, .min = (float)0xffffffffffffffff };
        for (int row = 0; row < df->nb_rows; row++)
            value_calc(df->data[row][col], &df_des, df->column_type[col]);
        printf("Column: %s\n", df->column_names[col]);
        printf("Count: %d\n", df->nb_rows);
        df_des.mean /= df->nb_rows;
        printf("Mean: %.2f\n", df_des.mean);
        for (int row = 0; row < df->nb_rows; row++)
            std_calc(df->data[row][col], &df_des, df->column_type[col]);
        df_des.std = sqrt((double)df_des.std / df->nb_rows);
        printf("Std: %.2f\n", df_des.std);
        printf("Min: %.2f\nMax: %.2f\n", df_des.min, df_des.max);
    }
}
