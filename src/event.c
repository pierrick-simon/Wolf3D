/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** event
*/

#include <math.h>
#include "wolf.h"

static void music_setvolume(sfEvent event, system_t *sys)
{
    float volume = sfMusic_getVolume(sys->music);

    if (is_keyboard_input(event, sfKeyF1)) {
        if (volume < 1)
            volume = VOL_MAX;
        else
            volume = VOL_MIN;
    }
    if (is_keyboard_input(event, sfKeyF2)) {
        if (volume > VOL_MIN + VOL_GAP)
            volume -= VOL_GAP;
        else
            volume = 0.0;
    }
    if (is_keyboard_input(event, sfKeyF3) && volume < VOL_MAX - VOL_GAP)
        volume += VOL_GAP;
    sfMusic_setVolume(sys->music, volume);
}

static void close_window(sfEvent event, system_t *sys)
{
    if (is_keyboard_input(event, sfKeyEscape) || event.type == sfEvtClosed) {
        sfRenderWindow_close(sys->window);
        sfMusic_setVolume(sys->music, VOL_MIN);
    }
}

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

static void resize_window(sfEvent event, system_t *sys)
{
    sfRenderWindow *new = NULL;
    sfBool old = sys->fullscreen;

    if (is_keyboard_input(event, sfKeyF11)) {
        if (sys->fullscreen == sfFalse) {
            new = create_window(sfFullscreen, 1);
            sys->fullscreen = sfTrue;
        } else {
            new = create_window(sfTitlebar | sfClose, 0.9);
            sys->fullscreen = sfFalse;
        }
        if (new != NULL) {
            sfRenderWindow_close(sys->window);
            sfRenderWindow_destroy(sys->window);
            sys->window = new;
        } else
            sys->fullscreen = old;
    }
}

void events(system_t *sys, game_t *game)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        close_window(event, sys);
        music_setvolume(event, sys);
        click(event, sys, game->weapon);
        change_weapon(event, sys, game->weapon);
        resize_window(event, sys);
    }
    game->player->fov = FOV;
    move_player(game->player);
}
