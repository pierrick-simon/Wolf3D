/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** get_offset
*/

#include <string.h>

int get_offset(char *str, int max_len)
{
    int len = strlen(str);

    return (max_len - len) / 2 + len;
}
