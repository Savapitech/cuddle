/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <limits.h>
#include <string.h>

#include "dataframe.h"
#include "copy_data.h"
#include "utils.h"

static
void *to_string(void *src, column_type_t src_type)
{
    char *result = NULL;

    if (src_type == BOOL)
        result = my_memdup(src, sizeof(char) * (strlen(src) + 1));
    if (src_type == INT)
        if (asprintf(&result, "%d", *(int *)src) == -1)
            return NULL;
    if (src_type == UINT)
        if (asprintf(&result, "%u", *(unsigned int *)src) == -1)
            return NULL;
    if (src_type == FLOAT)
        if (asprintf(&result, "%f", *(float *)src) == -1)
            return NULL;
    return result;
}

static
void *to_int(void *src, column_type_t src_type)
{
    int *result = malloc(sizeof(int));
    char *endptr;
    long value;

    if (!result)
        return NULL;
    if (src_type == BOOL)
        *result = (strcasecmp((char *)src, "true") == 0) ? 1 : 0;
    if (src_type == STRING) {
        value = strtol((char *)src, &endptr, 10);
        if (*endptr != '\0')
            return (free(result), NULL);
        *result = (int)value;
    }
    if (src_type == FLOAT)
        *result = (int)(*(float *)src);
    if (src_type == UINT)
        *result = (int)(*(unsigned int *)src);
    return result;
}

static
void *to_uint2(void *src, unsigned int *result)
{
    if (*(int *)src < 0)
        return (free(result), NULL);
    *result = (unsigned int)(*(int *)src);
    return result;
}

static
void *to_uint(void *src, column_type_t src_type)
{
    unsigned int *result = malloc(sizeof(unsigned int));
    char *endptr;
    unsigned long value;

    if (!result)
        return NULL;
    if (src_type == BOOL)
        *result = (strcasecmp((char *)src, "true") == 0) ? 1 : 0;
    if (src_type == STRING) {
        value = strtoul((char *)src, &endptr, 10);
        if (*endptr != '\0' || value > UINT_MAX)
            return (free(result), NULL);
        *result = (unsigned int)value;
    }
    if (src_type == FLOAT)
        *result = (unsigned int)(*(float *)src);
    if (src_type == INT)
        return to_uint2(src, result);
    return result;
}

static
void *to_float(void *src, column_type_t src_type)
{
    float *result = malloc(sizeof(float));
    char *endptr;

    if (!result)
        return NULL;
    if (src_type == BOOL)
        *result = (strcasecmp((char *)src, "true") == 0) ? 1.0F : 0.0F;
    if (src_type == STRING) {
        *result = strtof((char *)src, &endptr);
        if (*endptr != '\0') {
            free(result);
            return NULL;
        }
    }
    if (src_type == INT)
        *result = (float)(*(int *)src);
    if (src_type == UINT)
        *result = (float)(*(unsigned int *)src);
    return result;
}

static
void *to_bool(void *src, column_type_t src_type)
{
    char *result;
    int is_true = 0;

    if (src_type == STRING)
        is_true = (strlen((char *)src) > 0);
    if (src_type == INT)
        is_true = (*(int *)src != 0);
    if (src_type == UINT)
        is_true = (*(unsigned int *)src != 0);
    if (src_type == FLOAT)
        is_true = (*(float *)src != 0.0F);
    if (asprintf(&result, "%s", is_true ? "true" : "false") == -1)
        return NULL;
    return result;
}

static
void *get_type_data(void *src, column_type_t src_type, column_type_t downcast)
{
    switch (downcast) {
        case STRING:
            return to_string(src, src_type);
        case BOOL:
            return to_bool(src, src_type);
        case INT:
            return to_int(src, src_type);
        case UINT:
            return to_uint(src, src_type);
        case FLOAT:
            return to_float(src, src_type);
        default:
            return NULL;
    }
}

static
bool copy_col_values(type_data_t *d)
{
    size_t sz;

    for (int col = 0; col < d->src->nb_columns; col++) {
        if (col == d->col_idx &&
            d->src->column_type[d->col_idx] != d->downcast) {
            d->dst->data[d->row][col] = get_type_data(
                d->src->data[d->row][col], d->src->column_type[d->col_idx],
                d->downcast);
            continue;
        }
        sz = TYPES[d->src->column_type[col]].sz ?
            TYPES[d->src->column_type[col]].sz : strlen(
            (char *)d->src->data[d->row][col]) + 1;
        if (!sz)
            return false;
        d->dst->data[d->row][col] = my_memdup(d->src->data[d->row][col], sz);
        if (d->dst->data[d->row][col] == NULL)
            return false;
    }
    return true;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wanalyzer-malloc-leak"
static
dataframe_t *type_copy_data(dataframe_t *dst, dataframe_t *src,
    column_type_t downcast, int col_idx)
{
    type_data_t typ_dat = { .dst = dst, .src = src, .col_idx = col_idx,
        .downcast = downcast };

    for (int row = 0; row < src->nb_rows; row++) {
        dst->data[row] = (void **)malloc(sizeof(void *) *
            src->nb_columns);
        if ((void *)dst->data[row] == NULL)
            return NULL;
        typ_dat.row = row;
        if (!copy_col_values(&typ_dat))
            return (free((void *)dst->data[row]), NULL);
        if (dst->data[row][col_idx] == NULL)
            return NULL;
    }
    dst->nb_rows = src->nb_rows;
    dst->column_type[col_idx] = downcast;
    return dst;
}
#pragma GCC diagnostic pop

dataframe_t *df_to_type(dataframe_t *df, char const *column,
    column_type_t downcast)
{
    int col_idx;
    dataframe_t *new_df = malloc(sizeof(dataframe_t));

    if (new_df == NULL)
        return NULL;
    if (df == NULL || column == NULL || downcast == UNDEFINED)
        return (free(new_df), NULL);
    col_idx = get_col_idx(df, column);
    if (col_idx < 0)
        return (free(new_df), NULL);
    if (!copy_columns_type(new_df, df) || !copy_columns_name(new_df, df))
        return (free(new_df), NULL);
    new_df->data = (void ***)malloc(sizeof(void *) * df->nb_rows);
    if ((void *)new_df->data == NULL)
        return (free(new_df), NULL);
    new_df->separator = strdup(df->separator);
    if (new_df->separator == NULL)
        return ((free((void *)new_df->data), free(new_df)), NULL);
    new_df->nb_columns = df->nb_columns;
    return type_copy_data(new_df, df, downcast, col_idx);
}
