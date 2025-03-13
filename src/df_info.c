/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_info
*/

#include <stdio.h>

#include "dataframe.h"

void print_type(dataframe_t *dataframe, int a)
{
    switch (dataframe->column_type[a]) {
        case STRING:
            printf("string\n");
            break;
        case INT:
            printf("int\n");
            break;
        case UINT:
            printf("uint\n");
            break;
        case FLOAT:
            printf("float\n");
            break;
        default:
            printf("Unknown type !");
    }
}

void df_info(dataframe_t *dataframe)
{
    printf("%d columns\n", dataframe->nb_columns);
    for (int a = 0; a < dataframe->nb_columns; a++) {
        printf("- %s: ", dataframe->column_names[a]);
        print_type(dataframe, a);
    }
}
