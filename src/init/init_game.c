/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init
*/

#include "wolf.h"
#include <stdlib.h>

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

static int init_sound_texture(weapon_t *weapon)
{
    weapon->texture = malloc(sizeof(sfTexture *) * NB_WEAPON);
    weapon->sound = malloc(sizeof(sfMusic *) * NB_WEAPON);
    if (weapon->texture == NULL || weapon->sound == NULL)
        return ERROR;
    weapon->texture[PUNCH] = sfTexture_createFromFile("asset/punch.png", NULL);
    weapon->texture[PISTOL] =
        sfTexture_createFromFile("asset/pistol.png", NULL);
    weapon->texture[SHOTGUN] =
        (sfTexture *){sfTexture_createFromFile("asset/shotgun.png", NULL)};
    weapon->sound[PUNCH] =
        (sfMusic *){sfMusic_createFromFile("asset/fist_punch.ogg")};
    weapon->sound[PISTOL] =
        (sfMusic *){sfMusic_createFromFile("asset/pistol_shot.ogg")};
    weapon->sound[SHOTGUN] =
        (sfMusic *){sfMusic_createFromFile("asset/shotgun_shot.ogg")};
    for (int i = 0; i < NB_WEAPON; i++)
        if (weapon->texture[i] == NULL || weapon->sound[i] == NULL)
            return ERROR;
    return SUCCESS;
}

static int init_weapon_sprite(sprite_t *sprite)
{
    *sprite = (sprite_t){NULL};
    sprite->sprite = sfSprite_create();
    if (sprite->sprite == NULL)
        return ERROR;
    sprite->posf =
        (sfVector2f){WIN_WIDTH / 2, WIN_HEIGHT - WIN_HEIGHT + TOOLBAR_POS};
    sprite->rectangle =
        (sfIntRect){0, 0, WEAPON_SPRITE_X, WEAPON_SPRITE_Y};
    sprite->tile = 0;
    sprite->scale = (sfVector2f){2, 2};
    return SUCCESS;
}

static int init_weapon(weapon_t *weapon)
{
    *weapon = (weapon_t){NULL};
    weapon->shot = SEC_IN_MICRO * -1;
    weapon->weapon = 0;
    weapon->sprite = malloc(sizeof(sprite_t));
    if (weapon->sprite == NULL || init_weapon_sprite(weapon->sprite) == ERROR
        || init_sound_texture(weapon) == ERROR)
        return ERROR;
    sfSprite_setOrigin(weapon->sprite->sprite,
        (sfVector2f){WEAPON_SPRITE_X / 2, WEAPON_SPRITE_Y});
    sfSprite_setTexture(weapon->sprite->sprite,
        weapon->texture[weapon->weapon], sfTrue);
    sfSprite_setTextureRect(weapon->sprite->sprite, weapon->sprite->rectangle);
    sfSprite_setScale(weapon->sprite->sprite, weapon->sprite->scale);
    sfSprite_setPosition(weapon->sprite->sprite, weapon->sprite->posf);
    return SUCCESS;
}

static int init_state(map_t *map)
{
    map->wall_state.texture =
        sfTexture_createFromFile("asset/wall.png", NULL);
    map->wall_state.transform = sfTransform_Identity;
    map->wall_state.blendMode = sfBlendAlpha;
    if (map->wall_state.texture == NULL)
        return ERROR;
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
    map->rays = sfVertexArray_create();
    if (map->rays == NULL || init_state(map) == ERROR)
        return ERROR;
    sfVertexArray_setPrimitiveType(map->rays, sfLines);
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

void *init_game(void)
{
    game_t *game = malloc(sizeof(game_t));

    if (game == NULL)
        return NULL;
    *game = (game_t){NULL};
    game->map = malloc(sizeof(map_t));
    game->player = malloc(sizeof(player_t));
    game->weapon = malloc(sizeof(weapon_t));
    game->time_info = malloc(sizeof(time_info_t));
    if (game->map == NULL || init_map(game->map) == ERROR
        || game->player == NULL || game->weapon == NULL
        || init_weapon(game->weapon) == ERROR
        || init_player(game->player) == ERROR
        || init_time_info(game->time_info) == ERROR) {
        destroy_game(game);
        return NULL;
    }
    game->player->save = NULL;
    return (void *)game;
}
