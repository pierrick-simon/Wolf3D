/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_toolbar
*/

#include "game.h"
#include <stdlib.h>

static int init_toolbar_sprite_head(sprite_t *sprite)
{
    double scale = TOOLBAR_HEIGHT / HEAD_SPRITE_Y + 0.4;

    sprite->sprite = sfSprite_create();
    sprite->texture = sfTexture_createFromFile(str_asset[HEAD_ASSET], NULL);
    if (sprite->sprite == NULL || sprite->texture == NULL)
        return ERROR;
    sprite->rectangle =
        (sfIntRect){0, 0, HEAD_SPRITE_X, HEAD_SPRITE_Y};
    sprite->posf = (sfVector2f){WIN_WIDTH / 2, WIN_HEIGHT};
    sprite->scale = (sfVector2f){scale, scale};
    sfSprite_setPosition(sprite->sprite, sprite->posf);
    sfSprite_setTexture(sprite->sprite, sprite->texture, sfTrue);
    sfSprite_setTextureRect(sprite->sprite, sprite->rectangle);
    sfSprite_setScale(sprite->sprite, sprite->scale);
    sfSprite_setOrigin(
        sprite->sprite, (sfVector2f){HEAD_SPRITE_X / 2, HEAD_SPRITE_Y});
    return SUCCESS;
}

static int init_toolbar_sprite_light(sprite_t *sprite)
{
    sprite->sprite = sfSprite_create();
    sprite->texture = sfTexture_createFromFile(
        str_asset[FLASHLIGHT_ASSET], NULL);
    if (sprite->sprite == NULL || sprite->texture == NULL)
        return ERROR;
    sprite->rectangle =
        (sfIntRect){0, 0, FLASHLIGHT_SPRITE_X, FLASHLIGHT_SPRITE_Y};
    sprite->posf = (sfVector2f)
        {(float)WIN_WIDTH * FLASHLIGHT_COEF, WIN_HEIGHT};
    sfSprite_setPosition(sprite->sprite, sprite->posf);
    sfSprite_setTexture(sprite->sprite, sprite->texture, sfTrue);
    sfSprite_setTextureRect(sprite->sprite, sprite->rectangle);
    sfSprite_setOrigin(sprite->sprite,
        (sfVector2f){FLASHLIGHT_SPRITE_X / 2, FLASHLIGHT_SPRITE_Y});
    return SUCCESS;
}

int init_toolbar(toolbar_t *tool)
{
    tool->head = malloc(sizeof(sprite_t));
    tool->flashlight = malloc(sizeof(sprite_t));
    if (tool->head == NULL || init_toolbar_sprite_head(tool->head) == ERROR
        || tool->flashlight == NULL
        || init_toolbar_sprite_light(tool->flashlight) == ERROR)
        return ERROR;
    tool->rectangle = sfRectangleShape_create();
    tool->draw = init_from_conf(str_conf[CONF_TOOLBAR]);
    tool->background = sfTexture_createFromFile(
        str_asset[TOOLBAR_ASSET], NULL);
    tool->border = sfTexture_createFromFile(str_asset[BORDER_ASSET], NULL);
    if (tool->draw == NULL || tool->rectangle == NULL || tool->border == NULL)
        return ERROR;
    sfRectangleShape_setOutlineThickness(tool->rectangle, 2);
    tool->fps = sfFalse;
    tool->draw[TOOL_FPS].color = sfRed;
    tool->save = -1;
    tool->saving = sfFalse;
    tool->interact = sfFalse;
    return SUCCESS;
}
