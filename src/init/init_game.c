/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init
*/

#include "wolf.h"
#include <stdlib.h>

static int init_sound_texture(weapon_t *weapon)
{
    weapon->texture = malloc(sizeof(sfTexture *) * NB_WEAPON);
    weapon->sound = malloc(sizeof(sfMusic *) * NB_WEAPON);
    if (weapon->texture == NULL || weapon->sound == NULL)
        return EXIT_F;
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
            return EXIT_F;
    return EXIT_S;
}

static int init_weapon_sprite(sprite_t *sprite)
{
    *sprite = (sprite_t){NULL};
    sprite->sprite = sfSprite_create();
    if (sprite->sprite == NULL)
        return EXIT_F;
    sprite->posf =
        (sfVector2f){WIN_WIDTH / 2, WIN_HEIGHT - WIN_HEIGHT + TOOLBAR_POS};
    sprite->rectangle =
        (sfIntRect){0, 0, WEAPON_SPRITE_X, WEAPON_SPRITE_Y};
    sprite->tile = 0;
    sprite->scale = (sfVector2f){2, 2};
    return EXIT_S;
}

static int init_weapon(weapon_t *weapon)
{
    *weapon = (weapon_t){NULL};
    weapon->shot = SEC_IN_MICRO * -1;
    weapon->weapon = 0;
    weapon->sprite = malloc(sizeof(sprite_t));
    if (weapon->sprite == NULL || init_weapon_sprite(weapon->sprite) == EXIT_F
        || init_sound_texture(weapon) == EXIT_F)
        return EXIT_F;
    sfSprite_setOrigin(weapon->sprite->sprite,
        (sfVector2f){WEAPON_SPRITE_X / 2, WEAPON_SPRITE_Y});
    sfSprite_setTexture(weapon->sprite->sprite,
        weapon->texture[weapon->weapon], sfTrue);
    sfSprite_setTextureRect(weapon->sprite->sprite, weapon->sprite->rectangle);
    sfSprite_setScale(weapon->sprite->sprite, weapon->sprite->scale);
    sfSprite_setPosition(weapon->sprite->sprite, weapon->sprite->posf);
    return EXIT_S;
}

static int init_state(map_t *map)
{
    map->wall_state.texture =
        sfTexture_createFromFile("asset/wall.png", NULL);
    map->wall_state.transform = sfTransform_Identity;
    map->wall_state.blendMode = sfBlendAlpha;
    if (map->wall_state.texture == NULL)
        return EXIT_F;
    return EXIT_S;
}

static int init_map(map_t *map)
{
    sfVector2f pos = {WIN_WIDTH, WIN_HEIGHT / 2};

    *map = (map_t){NULL};
    map->ceiling_floor = sfRectangleShape_create();
    if (map->ceiling_floor == NULL)
        return EXIT_F;
    sfRectangleShape_setSize(map->ceiling_floor, pos);
    map->rays = sfVertexArray_create();
    if (map->rays == NULL || init_state(map) == EXIT_F)
        return EXIT_F;
    sfVertexArray_setPrimitiveType(map->rays, sfLines);
    return EXIT_S;
}

void init_player(player_t *player)
{
    player->angle = (-2 * M_PI) / 3;
    player->pos.x = (MAP_WIDTH * TILE_SIZE) / 2 - 92;
    player->pos.y = (MAP_HEIGHT * TILE_SIZE) / 2 - 92;
    player->type = NONE;
    player->v.x = 0;
    player->v.y = 0;
    player->fov = FOV;
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
    if (game->map == NULL || init_map(game->map) == EXIT_F
        || game->player == NULL || game->weapon == NULL
        || init_weapon(game->weapon) == EXIT_F) {
        destroy_game(game);
        return NULL;
    }
    init_player(game->player);
    return (void *)game;
}
