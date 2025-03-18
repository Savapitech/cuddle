/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** df_info
*/

#include <stdio.h>

#include "dataframe.h"

void df_info(dataframe_t *dataframe)
{
    printf("%d columns:\n", dataframe->nb_columns);
    for (int a = 0; a < dataframe->nb_columns; a++) {
        printf("- %s: %s\n", dataframe->column_names[a],
            TYPES[dataframe->column_type[a]].name);
    }
}
