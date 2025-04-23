/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** check
*/

#include "save.h"
#include "my.h"
#include <string.h>
#include <stdlib.h>

int check_size(char *str)
{
    if (strlen(str) > MAX_STRLEN || is_int_float(str) != NATURAL)
        return ERROR;
    return SUCCESS;
}

int check_pos(char *str)
{
    if (is_int_float(str) == MY_NAN || atof(str) < 0.0)
        return ERROR;
    return SUCCESS;
}

int check_angle(char *str)
{
    if (is_int_float(str) == MY_NAN)
        return ERROR;
    return SUCCESS;
}

int check_name(char *str)
{
    if (strlen(str ) > MAX_NAME)
        return ERROR;
    return SUCCESS;
}
