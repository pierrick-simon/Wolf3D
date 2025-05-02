/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init
*/

#include "game.h"
#include <stdlib.h>
#include <string.h>
#include "my.h"

static int init_crossair(crossair_t *crossair)
{
    crossair->circle = sfCircleShape_create();
    if (crossair->circle == NULL)
        return ERROR;
    sfCircleShape_setFillColor(crossair->circle, sfTransparent);
    sfCircleShape_setRadius(crossair->circle, 40.0);
    sfCircleShape_setOutlineThickness(crossair->circle, 3.0);
    sfCircleShape_setRadius(crossair->circle, CROSSAIR_RADIUS);
    sfCircleShape_setPosition(crossair->circle, (sfVector2f){(WIN_WIDTH / 2) -
        CROSSAIR_RADIUS, (WIN_HEIGHT / 2) - CROSSAIR_RADIUS});
    crossair->state.transform = sfTransform_Identity;
    crossair->state.blendMode = (sfBlendMode) {
        .colorSrcFactor = sfBlendFactorOneMinusDstColor,
        .colorDstFactor = sfBlendFactorOneMinusSrcColor,
        .colorEquation = sfBlendEquationAdd,
        .alphaSrcFactor = sfBlendFactorOne,
        .alphaDstFactor = sfBlendFactorZero,
        .alphaEquation = sfBlendEquationAdd
    };
    return SUCCESS;
}

static int init_state(map_t *map)
{
    map->wall_state.texture =
        sfTexture_createFromFile("asset/wall.png", NULL);
    if (map->wall_state.texture == NULL)
        return ERROR;
    map->wall_state.transform = sfTransform_Identity;
    map->wall_state.blendMode = sfBlendAlpha;
    return SUCCESS;
}

static int init_map(map_t *map)
{
    sfVector2f pos = {WIN_WIDTH, WIN_HEIGHT / 2};

    *map = (map_t){NULL};
    map->ceiling_floor = sfRectangleShape_create();
    if (map->ceiling_floor == NULL)
        return ERROR;
    sfRectangleShape_setSize(map->ceiling_floor, pos);
    map->quads = sfVertexArray_create();
    if (map->quads == NULL || init_state(map) == ERROR)
        return ERROR;
    sfVertexArray_setPrimitiveType(map->quads, sfQuads);
    return SUCCESS;
}

static int init_player(player_t *player)
{
    player->angle = 0;
    player->pos.x = -1;
    player->pos.y = -1;
    player->type = NONE;
    player->v.x = 0;
    player->v.y = 0;
    player->fov = FOV;
    player->is_sprinting = sfFalse;
    player->crossair = malloc(sizeof(crossair_t));
    if (player->crossair == NULL || init_crossair(player->crossair) == ERROR)
        return ERROR;
    return SUCCESS;
}

static int init_time_info(time_info_t *time_info)
{
    time_info->clock = sfClock_create();
    if (time_info->clock == NULL)
        return ERROR;
    time_info->time = 0;
    time_info->prev_time = 0;
    time_info->delta = 0.0;
    return SUCCESS;
}

static int init_toolbar_sprite(sprite_t *sprite)
{
    double scale = TOOLBAR_HEIGHT / HEAD_SPRITE_Y + 0.4;

    sprite->sprite = sfSprite_create();
    sprite->texture = sfTexture_createFromFile("asset/head.png", NULL);
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

static int init_toolbar(toolbar_t *tool)
{
    tool->head = malloc(sizeof(sprite_t));
    if (tool->head == NULL || init_toolbar_sprite(tool->head) == ERROR)
        return ERROR;
    tool->rectangle = sfRectangleShape_create();
    tool->draw = init_from_conf("config_file/toolbar.conf");
    if (tool->draw == NULL || tool->rectangle == NULL)
        return ERROR;
    sfRectangleShape_setOutlineThickness(tool->rectangle, 2);
    return SUCCESS;
}

void *init_game(void)
{
    game_t *game = malloc(sizeof(game_t));

    if (game == NULL)
        return NULL;
    *game = (game_t){NULL};
    game->tool = malloc(sizeof(toolbar_t));
    game->map = malloc(sizeof(map_t));
    game->player = malloc(sizeof(player_t));
    game->weapon = malloc(sizeof(weapon_t));
    game->time_info = malloc(sizeof(time_info_t));
    if (game->map == NULL || init_map(game->map) == ERROR
        || game->player == NULL || game->weapon == NULL
        || game->tool == NULL || init_toolbar(game->tool) == ERROR
        || init_weapons(game->weapon) == ERROR
        || init_player(game->player) == ERROR
        || init_time_info(game->time_info) == ERROR)
        return NULL;
    game->player->save = NULL;
    return (void *)game;
}
