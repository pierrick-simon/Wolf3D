/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** is_wall.c
*/

#include "wolf.h"

int is_wall(float x, float y)
{
    return map[(int)x][(int)y];
}