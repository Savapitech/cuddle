/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/dataframe.h"
#include "../src/debug.h"

bool sort_func(void *value1, void *value2)
{
    return *(int *) value1 > *(int *)value2;
}

static
void print_df(int rows, int col, void ***data, column_type_t type)
{
    switch (type) {
        case BOOL:
        case STRING:
            printf("[%s] ", (char *)data[rows][col]);
            break;
        case INT:
            printf("[%d] ", *(int *)data[rows][col]);
            break;
        case UINT:
            printf("[%d] ", *(uint32_t *)data[rows][col]);
            break;
        case FLOAT:
            printf("[%f] ", *(float *)data[rows][col]);
            break;
        default:
            printf("Unknown type !");
    }
}

int main(int ac, char **av)
{
    dataframe_t *df = df_read_csv(av[1], ",");

    if (df == NULL)
        return 84;
    U_DEBUG("nb_columns= %d\n", df->nb_columns);
    U_DEBUG("nb_rows= %d\n", df->nb_rows);
    U_DEBUG_MSG("columns: ");
    for (int a = 0; a < df->nb_columns; a++)
        printf("[%s] [%s]%s", df->column_names[a],
            TYPES[df->column_type[a]].name,
            a < df->nb_columns - 1 ? ", " : "\n");
    for (int rows = 0; rows < df->nb_rows; rows++) {
        for (int columns = 0; columns < df->nb_columns; columns++)
                print_df(rows, columns, df->data, df->column_type[columns]);
        puts("");
    }
    df_write_csv(df, "result.csv");
    free(df);
    return 0;
}
