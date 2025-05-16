/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_lose
*/

#include "quit.h"
#include <stdlib.h>

void destroy_lose(void *structure)
{
    lose_t *lose = (lose_t *)structure;

    if (lose->draw != NULL)
        free_draw_textbox(lose->draw, -1);
    if (lose->clock != NULL)
        sfClock_destroy(lose->clock);
    if (lose->spin_chair != NULL) {
        if (lose->spin_chair->texture != NULL)
            sfTexture_destroy(lose->spin_chair->texture);
        if (lose->spin_chair->sprite != NULL)
            sfSprite_destroy(lose->spin_chair->sprite);
        free(lose->spin_chair);
    }
    free(lose);
}
