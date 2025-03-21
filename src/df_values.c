/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <string.h>

#include "dataframe.h"
#include "utils.h"

void *df_get_value(dataframe_t *df, int row, char const *column)
{
    int col_idx;

    if (df == NULL || column == NULL || row > df->nb_rows)
        return NULL;
    col_idx = get_col_idx(df, column);
    if (col_idx < 0)
        return NULL;
    return df->data[row][col_idx];
}

void **df_get_values(dataframe_t *df, char const *column)
{
    int col_idx;
    void **result;

    if (df == NULL || column == NULL)
        return NULL;
    col_idx = get_col_idx(df, column);
    if (col_idx < 0)
        return NULL;
    result = (void **)malloc(sizeof(void *) * df->nb_rows);
    if ((void *)result == NULL)
        return NULL;
    for (int i = 0; i < df->nb_rows; i++)
        result[i] = df->data[i][col_idx];
    return result;
}

static
int compare_values(void *a, void *b, column_type_t type)
{
    switch (type) {
        case STRING:
            return strcmp((char *)a, (char *)b) == 0;
        case BOOL:
            return *(char *)a == *(char *)b;
        case INT:
            return *(int *)a == *(int *)b;
        case UINT:
            return *(unsigned int *)a == *(unsigned int *)b;
        case FLOAT:
            return *(float *)a == *(float *)b;
        default:
            return 0;
    }
}

static
int is_unique_value(void *value, void **unique_vl, int count,
    column_type_t type)
{
    int i;

    for (i = 0; i < count; i++)
        if (compare_values(value, unique_vl[i], type))
            return 0;
    return 1;
}

static
void **extract_unique_values(dataframe_t *df, int col_idx)
{
    int i;
    int unique_c = 0;
    void *cur_vl;
    void **unique_vl;

    if (!df || col_idx < 0 || col_idx >= df->nb_columns)
        return NULL;
    unique_vl = (void **)malloc((df->nb_rows + 1) * sizeof(void *));
    if (!unique_vl)
        return NULL;
    for (i = 0; i < df->nb_rows; i++) {
        cur_vl = df->data[i][col_idx];
        if (is_unique_value(cur_vl, unique_vl, unique_c,
                df->column_type[col_idx])) {
            unique_vl[unique_c] = cur_vl;
            unique_c++;
        }
    }
    unique_vl[unique_c] = NULL;
    return unique_vl;
}

void **df_get_unique_values(dataframe_t *df, char const *column)
{
    int col_idx;

    if (df == NULL || column == NULL)
        return NULL;
    col_idx = get_col_idx(df, column);
    if (col_idx < 0)
        return NULL;
    return extract_unique_values(df, col_idx);
}
