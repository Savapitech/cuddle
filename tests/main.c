/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "dataframe.h"
#include "debug.h"

bool sort_func(void *value1, void *value2)
{
    return *(int *) value1 > *(int *)value2;
}

bool filter_func(void *vl)
{
    return *(int *)vl > 30;
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
    dataframe_t *src = df_read_csv(av[1], ";");
    dataframe_t *df = df_filter(src, "age", filter_func);

    if (df == NULL)
        return 84;
    printf("nb_columns= %d\n", df->nb_columns);
    printf("nb_rows= %d\n", df->nb_rows);
#if defined(U_DEBUG_MODE)
    printf("columns: ");
    for (int a = 0; a < df->nb_columns; a++)
        printf("[%s] [%s]%s", df->column_names[a],
            TYPES[df->column_type[a]].name,
            a < df->nb_columns - 1 ? ", " : "\n");
#endif
    for (int rows = 0; rows < df->nb_rows; rows++) {
        for (int columns = 0; columns < df->nb_columns; columns++)
                print_df(rows, columns, df->data, df->column_type[columns]);
        puts("");
    }
    df_write_csv(df, "result.csv");
    df_free(src);
    df_free(df);
    return 0;
}
