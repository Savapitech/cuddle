/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdlib.h>
#include <stdio.h>

#include "../src/dataframe.h"

int main(int ac, char **av)
{
    dataframe_t *dataframe = df_read_csv(av[1], ",");

    if (dataframe == NULL)
        return 84;
    return 0;
}
