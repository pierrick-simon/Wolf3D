/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init
*/

#include "wolf.h"
#include <stdlib.h>

int init_sound_texture(weapon_t *weapon)
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

void init_map(map_t *map)
{
    sfVector2f pos = {WIN_WIDTH, WIN_HEIGHT / 2};

    map->ceiling_floor = sfRectangleShape_create();
    sfRectangleShape_setSize(map->ceiling_floor, pos);
}

int init_weapon(weapon_t *weapon)
{
    weapon->shot = SEC_IN_MICRO * -1;
    weapon->sprite.sprite = sfSprite_create();
    weapon->sprite.posf =
        (sfVector2f){WIN_WIDTH / 2, WIN_HEIGHT - WIN_HEIGHT + TOOLBAR_POS};
    weapon->sprite.rectangle =
        (sfIntRect){0, 0, WEAPON_SPRITE_X, WEAPON_SPRITE_Y};
    weapon->sprite.tile = 0;
    weapon->sprite.scale = (sfVector2f){2, 2};
    weapon->weapon = 0;
    if (weapon->sprite.sprite == NULL || init_sound_texture(weapon) == EXIT_F)
        return EXIT_F;
    sfSprite_setOrigin(weapon->sprite.sprite,
        (sfVector2f){WEAPON_SPRITE_X / 2, WEAPON_SPRITE_Y});
    sfSprite_setTexture(weapon->sprite.sprite,
        weapon->texture[weapon->weapon], sfTrue);
    sfSprite_setTextureRect(weapon->sprite.sprite, weapon->sprite.rectangle);
    sfSprite_setScale(weapon->sprite.sprite, weapon->sprite.scale);
    sfSprite_setPosition(weapon->sprite.sprite, weapon->sprite.posf);
    return EXIT_S;
}

static void init_state(game_t *game)
{
    game->wall_state.texture =
        sfTexture_createFromFile("asset/wall.png", NULL);
    game->wall_state.transform = sfTransform_Identity;
    game->wall_state.blendMode = sfBlendAlpha;
}

int init_game(game_t *game)
{
    game->window = create_window(sfTitlebar | sfClose, 0.9);
    game->clock = sfClock_create();
    game->music = sfMusic_createFromFile("asset/music.ogg");
    game->rays = sfVertexArray_create();
    init_state(game);
    if (game->window == NULL || game->clock == NULL
        || game->music == NULL || game->rays == NULL)
        return EXIT_F;
    game->fullscreen = sfFalse;
    sfVertexArray_setPrimitiveType(game->rays, sfLines);
    game->map = malloc(sizeof(map_t));
    if (game->map == NULL)
        return EXIT_F;
    init_map(game->map);
    game->player = malloc(sizeof(player_t));
    if (game->player == NULL)
        return EXIT_F;
    init_player(game->player);
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
