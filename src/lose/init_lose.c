/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_lose
*/

#include "quit.h"
#include <stdlib.h>

static int init_spin_chair(sprite_t *spin_chair)
{
    spin_chair->sprite = sfSprite_create();
    spin_chair->texture = sfTexture_createFromFile(
        str_asset[SPIN_ASSET], NULL);
    if (spin_chair->sprite == NULL || spin_chair->texture == NULL)
        return ERROR;
    spin_chair->rectangle = (sfIntRect){0, 0, CHAIR_WIDTH, CHAIR_HEIGHT};
    spin_chair->scale = (sfVector2f){CHAIR_SCALE, CHAIR_SCALE};
    spin_chair->tile = CHAIR_TILE;
    spin_chair->posf = (sfVector2f){CHAIR_WIDTH - CHAIR_OFFSET, WIN_HEIGHT};
    sfSprite_setTexture(spin_chair->sprite, spin_chair->texture, sfTrue);
    sfSprite_setTextureRect(spin_chair->sprite, spin_chair->rectangle);
    sfSprite_setOrigin(spin_chair->sprite,
        (sfVector2f){CHAIR_WIDTH / 2, CHAIR_HEIGHT});
    sfSprite_setScale(spin_chair->sprite, spin_chair->scale);
    sfSprite_setPosition(spin_chair->sprite, spin_chair->posf);
    return SUCCESS;
}

void *init_lose(void)
{
    lose_t *lose = malloc(sizeof(lose_t));

    if (lose == NULL)
        return NULL;
    lose->spin_chair = malloc(sizeof(sprite_t));
    if (lose->spin_chair == NULL || init_spin_chair(lose->spin_chair) == ERROR)
        return NULL;
    lose->str = LOSE_RESTART;
    lose->draw = init_from_conf(str_conf[CONF_LOSE]);
    lose->clock = sfClock_create();
    lose->name = malloc(sizeof(char) * (MAX_NAME_SCORE + 1));
    if (lose->draw == NULL || lose->clock == NULL || lose->name == NULL)
        return NULL;
    lose->name = "-----";
    lose->update = sfFalse;
    lose->draw[lose->str].color = sfRed;
    return (void *)lose;
}
