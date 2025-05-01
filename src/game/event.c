/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** event
*/

#include <math.h>
#include "wolf.h"

static void scroll_weapon(sfEvent event, weapon_t *weapon)
{
    if (is_input(event, sfKeyA, sfTrue, 4)) {
        if (weapon->weapon == PUNCH)
            weapon->weapon = SHOTGUN;
        else
            --weapon->weapon;
    }
    if (is_input(event, sfKeyE, sfTrue, 5)) {
        if (weapon->weapon == SHOTGUN)
            weapon->weapon = PUNCH;
        else
            ++weapon->weapon;
    }
}

static void change_weapon(weapon_t *weapon)
{
    fSprite_setOrigin(weapon->sprite,
        (sfVector2f){weapon->info[weapon->weapon].size.x / 2,
        weapon->info[weapon->weapon].size.y});
    sfSprite_setTexture(
        weapon->sprite, weapon->info[weapon->weapon].texture, sfTrue);
    sfSprite_setTextureRect(
        weapon->sprite, weapon->info[weapon->weapon].rectangle);
    sfSprite_setPosition(weapon->sprite, weapon->info[weapon->weapon].posf);
}

static void change_weapons(sfEvent event, weapon_t *weapon, sfInt64 time)
{
    double diff_shot = (double)(time - weapon->shot) / SEC_IN_MICRO;
    int prev = weapon->weapon;

    if (diff_shot < 0.3)
        return;
    scroll_weapon(event, weapon);
    if (is_input(event, sfKeyNum1, sfFalse, 0))
        weapon->weapon = PUNCH;
    if (is_input(event, sfKeyNum2, sfFalse, 0))
        weapon->weapon = PISTOL;
    if (is_input(event, sfKeyNum3, sfFalse, 0))
        weapon->weapon = SHOTGUN;
    if (is_input(event, 51, sfFalse, 0))
        weapon->weapon = MINIGUN;
    if (prev != weapon->weapon)
        change_weapon(weapon);
}

static void click(sfEvent event, weapon_t *weapon, sfInt64 time)
{
    double diff = (double)(time - weapon->shot) / SEC_IN_MICRO;

    if (diff < 0.4)
        return;
    if ((sfMouse_isButtonPressed(sfMouseLeft)) ||
        sfJoystick_getAxisPosition(0, sfJoystickR) > 0) {
        weapon->shot = time;
        sfMusic_play(weapon->info[weapon->weapon].sound);
    }
}

static void switch_scene(sfEvent event, state_info_t *state)
{
    if (is_input(event, sfKeyTab, sfTrue, 3)) {
        state->old_scene = state->scene;
        state->scene = PAUSE;
    }
}

void game_events(system_t *sys, game_t *game)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        change_weapons(event, game->weapon, game->time_info->time);
        switch_scene(event, sys->state);
    }
    click(event, game->weapon, game->time_info->time);
    move_player(game->player, game->time_info->delta);
}
