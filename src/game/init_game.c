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

static int init_crossair(player_t *player)
{
    player->crossair = sfCircleShape_create();
    if (player->crossair == NULL)
        return ERROR;
    sfCircleShape_setFillColor(player->crossair, sfTransparent);
    sfCircleShape_setRadius(player->crossair, 40.0);
    sfCircleShape_setOutlineThickness(player->crossair, 3.0);
    sfCircleShape_setRadius(player->crossair, CROSSAIR_RADIUS);
    sfCircleShape_setPosition(player->crossair, (sfVector2f){(WIN_WIDTH / 2) -
        CROSSAIR_RADIUS, (WIN_HEIGHT / 2) - CROSSAIR_RADIUS});
    return SUCCESS;
}

static int init_states(map_t *map)
{
    for (size_t i = 0; i < NB_WALL_TXT; ++i) {
        map->wall_states[i].texture =
            sfTexture_createFromFile(wall_textures[i].paths, NULL);
        if (map->wall_states[i].texture == NULL)
            return ERROR;
        map->wall_states[i].transform = sfTransform_Identity;
        map->wall_states[i].blendMode = sfBlendAlpha;
    }
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
    for (size_t i = 0; i < NB_WALL_TXT; ++i) {
        map->lines[i] = sfVertexArray_create();
        if (map->lines[i] == NULL || init_states(map) == ERROR)
            return ERROR;
        sfVertexArray_setPrimitiveType(map->lines[i], sfLines);
    }
    return SUCCESS;
}

static int init_player(player_t *player)
{
    player->angle = 0;
    player->pos.x = -1;
    player->pos.y = -1;
    player->type = NONE;
    player->center_ray.v.x = 0;
    player->center_ray.v.y = 0;
    player->center_ray.distance = 0.0;
    player->center_ray.type = NONE;
    player->fov = FOV;
    player->is_sprinting = sfFalse;
    if (init_crossair(player) == ERROR)
        return ERROR;
    return SUCCESS;
}

static int init_time_info(time_info_t *time_info)
{
    time_info->clock = sfClock_create();
    if (time_info->clock == NULL)
        return ERROR;
    time_info->time = 0;
    time_info->start_time = 0;
    time_info->end_time = 0;
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
    tool->background = sfTexture_createFromFile("asset/toolbar.png", NULL);
    if (tool->draw == NULL || tool->rectangle == NULL)
        return ERROR;
    sfRectangleShape_setOutlineThickness(tool->rectangle, 2);
    tool->fps = sfFalse;
    tool->draw[TOOL_FPS].color = sfRed;
    tool->save = -1;
    tool->saving = sfFalse;
    tool->interact = sfFalse;
    return SUCCESS;
}

static int init_music(sfMusic **music)
{
    music[DESTROY_WALL] = sfMusic_createFromFile("asset/destroy_wall.ogg");
    music[DOOR_MU] = sfMusic_createFromFile("asset/door.ogg");
    music[END_LEVEL] = sfMusic_createFromFile("asset/end_level.ogg");
    music[FOOTSTEPP] = sfMusic_createFromFile("asset/footstepps.ogg");
    for (int i = 0; i < NB_MUSIC; i++)
        if (music[i] == NULL)
            return ERROR;
    return SUCCESS;
}

static int check_init(game_t *game)
{
    if (game->map == NULL || init_map(game->map) == ERROR
        || game->player == NULL || game->weapon == NULL
        || game->tool == NULL || game->mini_map == NULL
        || init_toolbar(game->tool) == ERROR
        || init_weapons(game->weapon) == ERROR
        || init_player(game->player) == ERROR
        || init_time_info(game->time_info) == ERROR
        || init_music(game->music) == ERROR)
        return ERROR;
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
    game->mini_map = sfRectangleShape_create();
    if (check_init(game) == ERROR)
        return SUCCESS;
    game->player->save = NULL;
    return (void *)game;
}
