/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** event
*/

#include <math.h>
#include "wolf.h"

static void music_setvolume(sfEvent event, game_t *game)
{
    float volume = sfMusic_getVolume(game->music);

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
    sfMusic_setVolume(game->music, volume);
}

static void close_window(sfEvent event, game_t *game)
{
    if (is_keyboard_input(event, sfKeyEscape) || event.type == sfEvtClosed) {
        sfRenderWindow_close(game->window);
        sfMusic_setVolume(game->music, VOL_MIN);
    }
}

static void change_weapon(sfEvent event, game_t *game, weapon_t *weapon)
{
    int current = sfClock_getElapsedTime(game->clock).microseconds;
    double diff = (double)(current - weapon->shot) / SEC_IN_MICRO;

    if (diff < 0.3)
        return;
    if (is_keyboard_input(event, sfKeyNum1))
        weapon->weapon = PUNCH;
    if (is_keyboard_input(event, sfKeyNum2))
        weapon->weapon = PISTOL;
    if (is_keyboard_input(event, sfKeyNum3))
        weapon->weapon = SHOTGUN;
    sfSprite_setTexture(weapon->sprite.sprite,
        weapon->texture[weapon->weapon], sfTrue);
    sfSprite_setTextureRect(weapon->sprite.sprite, weapon->sprite.rectangle);
}

static void click(sfEvent event, game_t *game, weapon_t *weapon)
{
    int current = sfClock_getElapsedTime(game->clock).microseconds;
    double diff = (double)(current - weapon->shot) / SEC_IN_MICRO;

    if (diff < 0.4)
        return;
    if (event.type == sfEvtMouseButtonPressed
        && event.mouseButton.button == sfMouseLeft) {
        weapon->shot = sfClock_getElapsedTime(game->clock).microseconds;
        sfMusic_play(weapon->sound[weapon->weapon]);
    }
}

void events(game_t *game, weapon_t *weapon)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(game->window, &event)) {
        close_window(event, game);
        music_setvolume(event, game);
        click(event, game, weapon);
        change_weapon(event, game, weapon);
    }
    game->player->fov = FOV;
    move_player(game->player);
}
