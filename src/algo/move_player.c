/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** move_player.c
*/

#include "save.h"
#include "game.h"
#include "element.h"
#include <math.h>

static sfBool is_wall(float y, float x, save_t *save)
{
    if (save->map[(int)y / TILE_SIZE][(int)x / TILE_SIZE] != 0)
        return sfTrue;
    return sfFalse;
}

static int sprint(player_t *player, save_t *save, weapon_id_t id)
{
    int coef = 1;

    if ((sfKeyboard_isKeyPressed(sfKeyLShift) ||
        sfJoystick_getAxisPosition(0, sfJoystickZ) > 0)
        && id != MINIGUN) {
        player->is_sprinting = sfTrue;
        if (save->info->item_info[INFO_STAMINA] != 0) {
            coef = 2;
            player->fov = SPRINTING_FOV;
        }
    }
    if (is_wall(player->pos.y,
        player->pos.x + (v->x * coef * DISTANCE_COLISION),
        save) == sfFalse)
        player->pos.x += v->x * coef * FORWARD_COEF;
    if (is_wall(player->pos.y +
        (v->y * coef * DISTANCE_COLISION),
        player->pos.x, save) == sfFalse)
        player->pos.y += v->y * coef * FORWARD_COEF;
    return coef;
}

static int move_forward(game_t *game, save_t *save)
{
    if ((sfKeyboard_isKeyPressed(sfKeyUp))
        || sfKeyboard_isKeyPressed(sfKeyZ)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK) {
        return sprint(game->player, save, game->weapon->weapon);
    }
    return SKIP;
}

static int move_backward(player_t *player, save_t *save, sfVector2f *v)
{
    if ((sfKeyboard_isKeyPressed(sfKeyDown))
        || sfKeyboard_isKeyPressed(sfKeyS)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK) {
        if (is_wall(player->pos.y,
            player->pos.x - (v->x * DISTANCE_COLISION),
            save) == sfFalse)
            player->pos.x -= v->x;
        if (is_wall(player->pos.y -
            (v->y * DISTANCE_COLISION),
            player->pos.x, save) == sfFalse)
            player->pos.y -= v->y;
        return SUCCESS;
    }
    return SKIP;
}

static int move_left(player_t *player, save_t *save, int *head, sfVector2f *v)
{
    if (sfKeyboard_isKeyPressed(sfKeyQ)
        || sfJoystick_getAxisPosition(0, sfJoystickPovX) == - MAX_JOYSTICK) {
        *head -= HEAD_SPRITE_X;
        if (is_wall(player->pos.y,
            player->pos.x + (v->y * DISTANCE_COLISION),
            save) == sfFalse)
            player->pos.x += v->y;
        if (is_wall(player->pos.y -
            (v->x * DISTANCE_COLISION),
            player->pos.x, save) == sfFalse)
            player->pos.y -= v->x;
        return SUCCESS;
    }
    return SKIP;
}

static int move_right(player_t *player, save_t *save, int *head, sfVector2f *v)
{
    if (sfKeyboard_isKeyPressed(sfKeyD)
        || sfJoystick_getAxisPosition(0, sfJoystickPovX) == MAX_JOYSTICK) {
        *head += HEAD_SPRITE_X;
        if (is_wall(player->pos.y,
            player->pos.x - (v->y * DISTANCE_COLISION),
            save) == sfFalse)
            player->pos.x -= v->y;
        if (is_wall(player->pos.y +
            (v->x * DISTANCE_COLISION),
            player->pos.x, save) == sfFalse)
            player->pos.y += v->x;
        return SUCCESS;
    }
    return SKIP;
}

static void rotate_player(player_t *player, double delta, int *head)
{
    float x_controler = sfJoystick_getAxisPosition(0, sfJoystickU);

    if (fabs(x_controler) > 30)
        player->angle += ROTATION_SPEED * delta * (x_controler / 75);
    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        *head -= HEAD_SPRITE_X;
        player->angle -= ROTATION_SPEED * delta;
        if (player->angle < 0)
            player->angle += (M_PI * 2);
    }
    if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        player->angle += ROTATION_SPEED * delta;
        *head += HEAD_SPRITE_X;
        if (player->angle > (M_PI * 2))
            player->angle -= (M_PI * 2);
    }
}

static void set_music_pitch(int forward, int backward, sfMusic *footstepp)
{
    if ((forward == SKIP && backward == SKIP)
    || (forward > SUCCESS && backward == SKIP)
    || (forward == SKIP && backward == SUCCESS)
    || (forward == 2 && backward == SUCCESS))
        sfMusic_setPitch(footstepp, 1.0);
    if (forward == 1 && backward == SUCCESS)
        sfMusic_setPitch(footstepp, 0.85);
    if (forward == 2 && backward == SKIP)
        sfMusic_setPitch(footstepp, 1.3);
}

static void handle_footstepp(
    game_t *game, int *head, sfMusic *footstepp, player_t *player)
{
    sfSoundStatus music = sfMusic_getStatus(footstepp);
    int forward = move_forward(game, player->save);
    int backward = move_backward(player, player->save);

    set_music_pitch(forward, backward, footstepp);
    if (move_right(player, player->save, head, v)
        != move_left(player, player->save, head, v)
        || forward > SUCCESS || backward == SUCCESS) {
        if (music == sfStopped || music == sfPaused)
            sfMusic_play(footstepp);
    } else
        sfMusic_pause(footstepp);
}

void move_player(game_t *game, double delta, int *head, sfMusic *footstepp)
{
    center_ray(game->player);
    *head = HEAD_SPRITE_X;
    game->player->fov = FOV;
    game->player->is_sprinting = sfFalse;
    game->player->center_ray.v.x *= delta;
    game->player->center_ray.v.y *= delta;
    handle_footstepp(game, head, footstepp, game->player);
    rotate_player(game->player, delta, head);
    if (*head < 0)
        *head = 0;
    if (*head > HEAD_SPRITE_X * 2)
        *head = HEAD_SPRITE_X * 2;
}
