/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdlib.h>
#include <stdio.h>

#include "../src/dataframe.h"
#include "../src/debug.h"

int main(int ac, char **av)
{
    dataframe_t *dataframe = df_read_csv(av[1], ",");

    if (dataframe == NULL)
        return 84;
    printf("nb_columns= %d\n", dataframe->nb_columns);
    U_DEBUG("nb_rows= %d\n", dataframe->nb_rows);
    printf("name colmuns= %s\n", dataframe->column_names[0]);
    for (int a = 1; dataframe->column_names[a] != NULL; a++)
        printf("              %s\n", dataframe->column_names[a]);
    my_free_array(dataframe->column_names);
    //free(dataframe->column_names);
    free(dataframe);
    return 0;
}
