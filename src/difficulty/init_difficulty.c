/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_difficulty
*/

#include "game_menu.h"
#include <stdlib.h>

void *init_difficulty(void)
{
    difficulty_t *difficulty = malloc(sizeof(difficulty_t));

    if (difficulty == NULL)
        return NULL;
    difficulty->str = DIFF_THREE;
    difficulty->draw = init_from_conf(str_conf[CONF_DIFFICULTY]);
    if (difficulty->draw == NULL)
        return NULL;
    return (void *)difficulty;
}
