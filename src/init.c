/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** init
*/

#include "wolf.h"

void init_shotgun(shotgun_t *shotgun)
{
    shotgun->shot = SEC_IN_MICRO * -1;
    shotgun->sprite.texture = sfTexture_createFromFile("asset/shot_gun.png", NULL);
    shotgun->sprite.sprite = sfSprite_create();
    shotgun->sprite.posf = (sfVector2f){WIN_WIDTH / 2, WIN_HEIGHT};
    shotgun->sprite.rectangle = (sfIntRect){0, 0, SHOTGUN_SPRITE.x, SHOTGUN_SPRITE.y};
    shotgun->sprite.tile = 0;
    shotgun->sprite.scale = (sfVector2f){2, 2};
    shotgun->sound = sfMusic_createFromFile("asset/gun_shot.ogg");
    sfSprite_setOrigin(shotgun->sprite.sprite, (sfVector2f){SHOTGUN_SPRITE.x / 2, SHOTGUN_SPRITE.y});
    sfSprite_setTexture(shotgun->sprite.sprite, shotgun->sprite.texture, sfTrue);
    sfSprite_setTextureRect(shotgun->sprite.sprite, shotgun->sprite.rectangle);
    sfSprite_setScale(shotgun->sprite.sprite, shotgun->sprite.scale);
    sfSprite_setPosition(shotgun->sprite.sprite, shotgun->sprite.posf);
}

void init_game(game_t *game)
{
    game->window = create_window();
    game->clock = sfClock_create();
    game->music = sfMusic_createFromFile("asset/music.ogg");
}
