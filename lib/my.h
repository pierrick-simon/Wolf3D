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

char **my_str_to_word_array(
    char const *str, char const *sep, char const *stay_sep);
char *open_file(const char *file);
void free_array(char **array);
int array_len(char **array);

#endif
