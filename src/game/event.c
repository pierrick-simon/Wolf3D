/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** event
*/

#include <math.h>
#include "wolf.h"

static void change_weapon(sfEvent event, system_t *sys, weapon_t *weapon)
{
    int current = sfClock_getElapsedTime(sys->clock).microseconds;
    double diff = (double)(current - weapon->shot) / SEC_IN_MICRO;

    if (diff < 0.3)
        return;
    if (is_keyboard_input(event, sfKeyNum1))
        weapon->weapon = PUNCH;
    if (is_keyboard_input(event, sfKeyNum2))
        weapon->weapon = PISTOL;
    if (is_keyboard_input(event, sfKeyNum3))
        weapon->weapon = SHOTGUN;
    sfSprite_setTexture(weapon->sprite->sprite,
        weapon->texture[weapon->weapon], sfTrue);
    sfSprite_setTextureRect(weapon->sprite->sprite, weapon->sprite->rectangle);
}

static void click(sfEvent event, system_t *sys, weapon_t *weapon)
{
    int current = sfClock_getElapsedTime(sys->clock).microseconds;
    double diff = (double)(current - weapon->shot) / SEC_IN_MICRO;

    if (diff < 0.4)
        return;
    if (event.type == sfEvtMouseButtonPressed
        && event.mouseButton.button == sfMouseLeft) {
        weapon->shot = sfClock_getElapsedTime(sys->clock).microseconds;
        sfMusic_play(weapon->sound[weapon->weapon]);
    }
}

void game_events(system_t *sys, game_t *game)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        click(event, sys, game->weapon);
        change_weapon(event, sys, game->weapon);
    }
    game->player->fov = FOV;
    game->player->is_sprinting = sfFalse;
    move_player(game->player);
}
