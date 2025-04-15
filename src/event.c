/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** event
*/

#include <math.h>
#include "wolf.h"

static sfBool is_keyboard_input(sfEvent event, sfKeyCode key)
{
    if (event.type == sfEvtKeyPressed && event.key.code == key)
        return sfTrue;
    return sfFalse;
}

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

static void change_weapon(sfEvent event, weapon_t *weapon)
{
    if (is_keyboard_input(event, sfKeyNum1))
        weapon->weapon = 0;
    if (is_keyboard_input(event, sfKeyNum2))
        weapon->weapon = 1;
    if (is_keyboard_input(event, sfKeyNum3))
        weapon->weapon = 2;
    sfSprite_setTexture(weapon->sprite.sprite,
        weapon->texture[weapon->weapon], sfTrue);
    sfSprite_setTextureRect(weapon->sprite.sprite, weapon->sprite.rectangle);
}

static void click(sfEvent event, game_t *game, weapon_t *weapon)
{
    if (event.type == sfEvtMouseButtonPressed
        && event.mouseButton.button == sfMouseLeft) {
        weapon->shot = sfClock_getElapsedTime(game->clock).microseconds;
        sfMusic_play(weapon->sound[weapon->weapon]);
    }
}

static void move_player(sfEvent event, game_t *game, player_t *player)
{
    sfVector2f v = (sfVector2f){cos(player->angle), sin(player->angle)};

    if (is_keyboard_input(event, sfKeyZ)) {
        player->x += v.x;
        player->y += v.y;
    }
    if (is_keyboard_input(event, sfKeyS)) {
        player->x -= v.x;
        player->y -= v.y;
    }
    if (is_keyboard_input(event, sfKeyQ)) {
        player->x += v.x;
        player->y -= v.y;
    }
    if (is_keyboard_input(event, sfKeyD)) {
        player->x -= v.x;
        player->y += v.y;
    }
    if (is_keyboard_input(event, sfKeyLeft))
        player->angle -= 0.1;
    if (is_keyboard_input(event, sfKeyRight))
        player->angle += 0.1;
}

void events(game_t *game, weapon_t *weapon)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(game->window, &event)) {
        close_window(event, game);
        music_setvolume(event, game);
        click(event, game, weapon);
        change_weapon(event, weapon);
        move_player(event, game, game->player);
    }
}
