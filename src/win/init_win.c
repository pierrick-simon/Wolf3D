/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_win
*/

#include "quit.h"
#include <stdlib.h>

static int init_danse(sprite_t *danse)
{
    danse->sprite = sfSprite_create();
    danse->texture = sfTexture_createFromFile("asset/danse.png", NULL);
    if (danse->sprite == NULL || danse->texture == NULL)
        return ERROR;
    danse->rectangle = (sfIntRect){0, 0, DANSE_WIDTH, DANSE_HEIGHT};
    danse->tile = DANSE_TILE;
    danse->scale = (sfVector2f){DANSE_SCALE, DANSE_SCALE};
    danse->posf = (sfVector2f){0, WIN_HEIGHT};
    sfSprite_setTexture(danse->sprite, danse->texture, sfTrue);
    sfSprite_setTextureRect(danse->sprite, danse->rectangle);
    sfSprite_setOrigin(danse->sprite, (sfVector2f){0, DANSE_HEIGHT});
    sfSprite_setScale(danse->sprite, danse->scale);
    sfSprite_setPosition(danse->sprite, danse->posf);
    return SUCCESS;
}

void *init_win(void)
{
    win_t *win = malloc(sizeof(win_t));

    if (win == NULL)
        return NULL;
    win->danse = malloc(sizeof(sprite_t));
    if (win->danse == NULL || init_danse(win->danse) == ERROR)
        return NULL;
    win->str = WIN_ENTER;
    win->draw = init_from_conf("config_file/win.conf");
    win->clock = sfClock_create();
    win->name = malloc(sizeof(char) * (MAX_NAME_SCORE + 1));
    if (win->draw == NULL || win->clock == NULL || win->name == NULL)
        return NULL;
    for (int i = 0; i <= MAX_NAME_SCORE; i++)
        win->name[i] = '\0';
    win->update = sfFalse;
    return (void *)win;
}
