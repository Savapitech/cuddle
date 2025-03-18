/*
** EPITECH PROJECT, 2025
** cuddle
** File description:
** dataframe
*/

#ifndef DATAFRAME_H_
    #define DATAFRAME_H_
    #include <math.h>
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>

    #define WC(fd, str) write(fd, str, sizeof str - 1)
    #define IDX_OF(array, i, mem_s) (array + ((i) * (mem_s)))
    #define ABS(v) (((v) < (0)) ? -(v) : (v))

typedef enum {
    BOOL,
    INT,
    UINT,
    FLOAT,
    STRING,
    UNDEFINED
} column_type_t;

    #define TYPES_NB 5

typedef struct {
    char const *name;
    size_t sz;
} types_t;

typedef struct dataframe_shape_s {
    int nb_rows;
    int nb_columns;
} dataframe_shape_t;

typedef struct dataframe_s {
    int nb_rows;
    int nb_columns;
    char **column_names;
    column_type_t *column_type;
    void ***data;
    char *separator;
} dataframe_t;

typedef struct {
    float mean;
    float std;
    float min;
    float max;
} df_describe_t;

extern const types_t TYPES[];

// Core
dataframe_t *df_read_csv(const char *filename, const char *separator);
dataframe_t *df_head(dataframe_t *df, int nb_rows);
dataframe_t *df_tail(dataframe_t *df, int nb_rows);
void df_info(dataframe_t *dataframe);
void df_describe(dataframe_t *df);
int df_write_csv(dataframe_t *df, char const *path);
dataframe_t *df_sort(dataframe_t *df, char const *column,
    bool (*sort_func)(void *vl1, void *vl2));
dataframe_shape_t df_shape(dataframe_t *df);
void df_free(dataframe_t *df);
dataframe_t *df_filter(dataframe_t *df, const char *column,
    bool (*filter_func)(void *vl));
void *df_get_value(dataframe_t *df, int row, char const *column);
void **df_get_values(dataframe_t *df, char const *column);
#endif /* !DATAFRAME_H_ */
