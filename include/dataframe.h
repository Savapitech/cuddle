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
dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows);
void df_info(dataframe_t *dataframe);
void df_describe(dataframe_t *df);
int df_write_csv(dataframe_t *df, char const *path);
dataframe_t *df_sort(dataframe_t *df, char const *column,
    bool (*sort_func)(void *vl1, void *vl2));

// Utils (will me moved to another header)
char **my_str_to_word_array(const char *str, const char *separator);
void my_free_array(char **array);
void free_data(void ***data, int nb_columns, int nb_rows);
void *my_memdup(const uint8_t *mem, size_t bytes);
bool data_storage(dataframe_t *dataframe, char **file, const char *separator);
void mini_qsort(void ***arr, size_t size, int col,
    bool compare(void *, void *));

#endif /* !DATAFRAME_H_ */
