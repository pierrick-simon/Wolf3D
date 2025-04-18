/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** event
*/

#include <math.h>
#include "wolf.h"

static void change_weapon(sfEvent event, weapon_t *weapon, sfInt64 time)
{
    double diff = (double)(time - weapon->shot) / SEC_IN_MICRO;

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

static void click(sfEvent event, weapon_t *weapon, sfInt64 time)
{
    double diff = (double)(time - weapon->shot) / SEC_IN_MICRO;

    if (diff < 0.4)
        return;
    if (event.type == sfEvtMouseButtonPressed
        && event.mouseButton.button == sfMouseLeft) {
        weapon->shot = time;
        sfMusic_play(weapon->sound[weapon->weapon]);
    }
}

void game_events(system_t *sys, game_t *game)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        click(event, game->weapon, game->time_info->time);
        change_weapon(event, game->weapon, game->time_info->time);
    }
    move_player(game->player, game->time_info->delta);
}
