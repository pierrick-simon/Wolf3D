/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init
*/

#include "wolf.h"
#include <stdlib.h>

void init_sound_texture(weapon_t *weapon)
{
    weapon->texture = malloc(sizeof(sfTexture *) * 3);
    weapon->sound = malloc(sizeof(sfMusic *) * 3);
    weapon->texture[0] = sfTexture_createFromFile("asset/punch.png", NULL);
    weapon->texture[1] = sfTexture_createFromFile("asset/pistol.png", NULL);
    weapon->texture[2] =
        (sfTexture *){sfTexture_createFromFile("asset/shotgun.png", NULL)};
    weapon->sound[0] =
        (sfMusic *){sfMusic_createFromFile("asset/fist_punch.ogg")};
    weapon->sound[1] =
        (sfMusic *){sfMusic_createFromFile("asset/pistol_shot.ogg")};
    weapon->sound[2] =
        (sfMusic *){sfMusic_createFromFile("asset/shotgun_shot.ogg")};
}

void init_map(map_t *map)
{
    sfVector2f pos = {WIN_WIDTH, WIN_HEIGHT / 2};

    map->ceiling_floor = sfRectangleShape_create();
    sfRectangleShape_setSize(map->ceiling_floor, pos);
    map->ceiling_color = CEILING_COLOR;
    map->floor_color = FLOOR_COLOR;
}

void init_weapon(weapon_t *weapon)
{
    weapon->shot = SEC_IN_MICRO * -1;
    weapon->sprite.sprite = sfSprite_create();
    weapon->sprite.posf = (sfVector2f){WIN_WIDTH / 2, WIN_HEIGHT};
    weapon->sprite.rectangle =
        (sfIntRect){0, 0, SHOTGUN_SPRITE_X, SHOTGUN_SPRITE_Y};
    weapon->sprite.tile = 0;
    weapon->sprite.scale = (sfVector2f){2, 2};
    weapon->weapon = 0;
    init_sound_texture(weapon);
    sfSprite_setOrigin(weapon->sprite.sprite,
        (sfVector2f){SHOTGUN_SPRITE_X / 2, SHOTGUN_SPRITE_Y});
    sfSprite_setTexture(weapon->sprite.sprite,
        weapon->texture[weapon->weapon], sfTrue);
    sfSprite_setTextureRect(weapon->sprite.sprite, weapon->sprite.rectangle);
    sfSprite_setScale(weapon->sprite.sprite, weapon->sprite.scale);
    sfSprite_setPosition(weapon->sprite.sprite, weapon->sprite.posf);
}

void init_game(game_t *game)
{
    game->window = create_window();
    game->clock = sfClock_create();
    game->music = sfMusic_createFromFile("asset/music.ogg");
    game->map = malloc(sizeof(map_t));
    if (game->map == NULL)
        return;
    init_map(game->map);
    game->player = malloc(sizeof(player_t));
    if (game->player == NULL)
        return;
    init_player(game->player);
}

void init_player(player_t *player)
{
    player->angle = (2 * M_PI) / 3;
    player->x = (MAP_WIDTH) / 2 - 0.1;
    player->y = (MAP_HEIGHT) / 2 - 0.1;
}
