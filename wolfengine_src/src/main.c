/*
** EPITECH PROJECT, 2025
** wolfengine
** File description:
** main.c
*/

#include <stddef.h>
#include <stdio.h>
#include "wolfengine.h"

int main(int ac, char **av, char **env)
{
    if (ac == 0 || av == NULL || env == NULL)
        printf("[...]\n");
    if (start() == EXIT_F)
        return EXIT_F;
    return EXIT_S;
}
