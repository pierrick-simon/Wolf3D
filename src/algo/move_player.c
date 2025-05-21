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

static int sprint(player_t *player,
    save_t *save, sfVector2f *v, weapon_id_t id)
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

static int move_forward(save_t *save, sfVector2f *v, game_t *game)
{
    if ((sfKeyboard_isKeyPressed(sfKeyUp))
        || sfKeyboard_isKeyPressed(sfKeyZ)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK) {
        return sprint(game->player, save, v, game->weapon->weapon);
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
    game_t *game, int *head, sfMusic *footstepp, sfVector2f *v)
{
    sfSoundStatus music = sfMusic_getStatus(footstepp);
    int forward = move_forward(game->player->save, v, game);
    int backward = move_backward(game->player, game->player->save, v);

    set_music_pitch(forward, backward, footstepp);
    if (move_right(game->player, game->player->save, head, v)
        != move_left(game->player, game->player->save, head, v)
        || forward > SUCCESS || backward == SUCCESS) {
        if (music == sfStopped || music == sfPaused)
            sfMusic_play(footstepp);
    } else
        sfMusic_pause(footstepp);
}

void move_player(game_t *game, double delta, int *head, sfMusic *footstepp)
{
    sfVector2f v = {0};

    center_ray(game->player);
    v = game->player->center_ray.v;
    *head = HEAD_SPRITE_X;
    game->player->fov = FOV;
    game->player->is_sprinting = sfFalse;
    v.x *= delta * PLAYER_SPEED;
    v.y *= delta * PLAYER_SPEED;
    handle_footstepp(game, head, footstepp, &v);
    rotate_player(game->player, delta, head);
    if (*head < 0)
        *head = 0;
    if (*head > HEAD_SPRITE_X * 2)
        *head = HEAD_SPRITE_X * 2;
}
