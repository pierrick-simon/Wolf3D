/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_difficulty
*/

#include "game_menu.h"
#include <stdlib.h>

void destroy_difficulty(void *structure)
{
    difficulty_t *difficulty = (difficulty_t *)structure;

    if (difficulty->draw != NULL)
        free_draw_textbox(difficulty->draw, -1);
    free(difficulty);
}
