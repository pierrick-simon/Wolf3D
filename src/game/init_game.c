/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init
*/

#include "game.h"
#include "linked_list.h"
#include "entities.h"
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
    map->wall_states.texture =
        sfTexture_createFromFile("asset/walls.png", NULL);
    if (map->wall_states.texture == NULL)
        return ERROR;
    map->wall_states.transform = sfTransform_Identity;
    map->wall_states.blendMode = sfBlendAlpha;
    return SUCCESS;
}

static int init_map_info(map_t *map)
{
    sfVector2f pos = {WIN_WIDTH, WIN_HEIGHT / 2};

    *map = (map_t){NULL};
    map->ceiling_floor = sfRectangleShape_create();
    if (map->ceiling_floor == NULL)
        return ERROR;
    sfRectangleShape_setSize(map->ceiling_floor, pos);
    map->line = sfVertexArray_create();
    if (map->line == NULL || init_states(map) == ERROR)
        return ERROR;
    sfVertexArray_setPrimitiveType(map->line, sfLines);
    map->entity_center = NO_ENTITIE;
    return SUCCESS;
}

static int init_player(player_t *player)
{
    player->angle = 0;
    player->pos.x = -1;
    player->pos.y = -1;
    player->center_ray.v.x = 0;
    player->center_ray.v.y = 0;
    player->center_ray.distance = 0.0;
    player->center_ray.type = NONE;
    player->fov = FOV;
    player->is_sprinting = sfFalse;
    player->jump_value = 0;
    player->status = S_NONE;
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
    time_info->shot = 0;
    time_info->weapon = 0;
    time_info->item = 0;
    return SUCCESS;
}

static int init_music(sfMusic **music)
{
    music[DESTROY_WALL] = sfMusic_createFromFile("asset/destroy_wall.ogg");
    music[DOOR_MU] = sfMusic_createFromFile("asset/door.ogg");
    music[END_LEVEL] = sfMusic_createFromFile("asset/end_level.ogg");
    music[FOOTSTEPS] = sfMusic_createFromFile("asset/footsteps.ogg");
    music[HURT] = sfMusic_createFromFile("asset/hurt.ogg");
    music[PICK_UP] = sfMusic_createFromFile("asset/pick_up.ogg");
    for (int i = 0; i < NB_MUSIC; i++)
        if (music[i] == NULL)
            return ERROR;
    return SUCCESS;
}

static void init_light_info(light_t *light)
{
    light->flash_on = sfFalse;
    light->night_on = sfFalse;
    light->sec = 1;
    sfSprite_setTexture(light->night, light->night_texture, sfTrue);
    sfRectangleShape_setSize(light->overlay,
        (sfVector2f){WIN_WIDTH, WIN_HEIGHT});
    sfRectangleShape_setFillColor(light->overlay, sfTransparent);
    sfCircleShape_setRadius(light->flashlight, FLASHLIGHT);
    sfCircleShape_setOrigin(light->flashlight,
        (sfVector2f){FLASHLIGHT, FLASHLIGHT});
    sfCircleShape_setFillColor(light->flashlight, sfTransparent);
    sfCircleShape_setPosition(light->flashlight,
        (sfVector2f){WIN_WIDTH / 2, WIN_HEIGHT / 2});
}

static int init_light(light_t *light)
{
    light->night_render = sfRenderTexture_create(
        WIN_WIDTH, WIN_HEIGHT, sfFalse);
    light->night = sfSprite_create();
    light->overlay = sfRectangleShape_create();
    light->flashlight = sfCircleShape_create();
    if (light->night_render == NULL || light->night == NULL
        || light->overlay == NULL || light->flashlight == NULL)
        return ERROR;
    light->state = (sfRenderStates){.blendMode = sfBlendNone,
        .transform = sfTransform_Identity, .texture = NULL, .shader = NULL};
    light->night_texture = sfRenderTexture_getTexture(light->night_render);
    if (light->night_texture == NULL)
        return ERROR;
    init_light_info(light);
    return SUCCESS;
}

static int check_init(game_t *game)
{
    if (game->map == NULL || game->cursor == NULL
        || game->player == NULL || game->weapon == NULL
        || game->tool == NULL || game->mini_map == NULL
        || game->light == NULL || init_light(game->light) == ERROR
        || init_toolbar(game->tool) == ERROR
        || init_weapons(game->weapon) == ERROR
        || init_player(game->player) == ERROR
        || init_map_info(game->map) == ERROR
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
    game->light = malloc(sizeof(light_t));
    game->mini_map = sfRectangleShape_create();
    game->cursor = sfCircleShape_create();
    if (check_init(game) == ERROR || init_render_state(game) == ERROR)
        return SUCCESS;
    game->player->save = NULL;
    sfCircleShape_setRadius(game->cursor, MINI_MAP_CURSOR);
    sfCircleShape_setOrigin(game->cursor,
        (sfVector2f){MINI_MAP_CURSOR, MINI_MAP_CURSOR});
    return (void *)game;
}
