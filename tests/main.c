/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void *apply_func(void *value)
{
    char *str = strdup((char *)value);

    if (str == NULL)
        return NULL;
    if (str[strlen(str) - 1] == 'e')
        str[strlen(str) - 1] = '\0';
    return str;
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
    dataframe_t *src = df_read_csv(av[1], NULL);
    dataframe_t *int_df = df_apply(src, "amount", apply_func);
    dataframe_t *dst = df_to_type(int_df, "amount", INT);
    dataframe_t *df = df_sort(dst, "amount", sort_func);

    if (df == NULL)
        return 84;
    df_write_csv(df, "result.csv");
    printf("nb_columns= %d\n", df->nb_columns);
    printf("nb_rows= %d\n", df->nb_rows);
    df_info(df);
    df_describe(df);
    df_shape(df);
    df_filter(df, "amount", filter_func);
    df_head(df, 1);
    df_tail(df, 1);
    df_get_value(df, 0, "amount");
    df_get_values(df, "amount");
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
    df_free(src);
    df_free(df);
    df_free(int_df);
    df_free(dst);
    return 0;
}
