/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** lib
*/

#ifndef MY_H_
    #define MY_H_

    #define LIB_SUCCESS 0
    #define LIB_ERROR 84

typedef enum {
    NATURAL,
    INTEGER,
    RATIONAL,
    MY_NAN,
} nb_group_t;

int is_int_float(char *av);
char **my_str_to_word_array(
    char const *str, char const *sep, char const *stay_sep);
char *open_file(const char *file);
void free_array(char **array);
int array_len(char **array);
int get_nblen(int nb);
char **get_tab(const char *file);
int get_offset(char *str, int max_len);

#endif
