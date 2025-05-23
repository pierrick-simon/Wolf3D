/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_difficulty
*/

#include "game_menu.h"
#include "save.h"
#include "my.h"
#include <stdio.h>

void draw_difficulty(system_t *sys, void *structure)
{
    difficulty_t *difficulty = (difficulty_t *)structure;

    difficulty_events(sys, difficulty);
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    for (int i = 0; i < NB_DIFFICULTY; i++)
        draw_string(sys, sys->textbox, &difficulty->draw[i]);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
}
