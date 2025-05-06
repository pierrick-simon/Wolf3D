/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** event
*/

#include <math.h>
#include "save.h"
#include "game.h"

static void scroll_weapon(sfEvent event, weapon_t *weapon)
{
    sfBool minus = is_input(event, sfKeyA, sfTrue, 4);
    sfBool plus = is_input(event, sfKeyE, sfTrue, 5);

    do {
    if (minus)
        --weapon->weapon;
    if (plus)
        ++weapon->weapon;
    if (weapon->weapon == NB_WEAPON)
        weapon->weapon = PUNCH;
    if (weapon->weapon == NO_WEAPON)
        weapon->weapon = MINIGUN;
    } while (weapon->info[weapon->weapon].bag != sfTrue);
}

static void change_weapon(weapon_t *weapon)
{
    sfSprite_setOrigin(weapon->sprite,
        (sfVector2f){weapon->info[weapon->weapon].size.x / 2,
        weapon->info[weapon->weapon].size.y});
    sfSprite_setTexture(
        weapon->sprite, weapon->info[weapon->weapon].texture, sfTrue);
    sfSprite_setTextureRect(
        weapon->sprite, weapon->info[weapon->weapon].rectangle);
    sfSprite_setPosition(weapon->sprite, weapon->info[weapon->weapon].posf);
}

static void change_weapons(sfEvent event, game_t *game, weapon_t *weapon)
{
    weapon_id_t prev = weapon->weapon;

    if (weapon->info[weapon->weapon].current_tile != 0)
        return;
    game->tool->draw[prev + TOOL_ONE].color = sfWhite;
    scroll_weapon(event, weapon);
    for (int i = 0; i < NB_WEAPON; i++) {
        if (is_input(event, weapon->info[i].key, sfFalse, 0)
        && weapon->info[i].bag == sfTrue)
        weapon->weapon = i;
    }
    if (prev != weapon->weapon)
        change_weapon(weapon);
    game->tool->draw[weapon->weapon + TOOL_ONE].color = sfRed;
}

static void destroy_wall(int **map, player_t *player, game_t *game)
{
    sfVector2i casted_pos = cast_pos(&player->center_ray.pos,
        player->center_ray.type);

    if (casted_pos.x < 0 || casted_pos.y < 0)
        return;
    for (weapon_id_t i = 0; i < NB_WEAPON; ++i) {
        if (game->weapon->weapon == i && map[casted_pos.y][casted_pos.x] == 3
            && game->weapon->info[i].range > player->center_ray.distance)
            map[casted_pos.y][casted_pos.x] = 0;
    }
}

static void click(system_t *sys,
    weapon_t *weapon, sfInt64 time, game_t *game)
{
    double diff = (double)(time - weapon->shot) / SEC_IN_MICRO;
    int ind = weapon->weapon;

    if (diff < weapon->info[ind].speed * weapon->info[ind].nb_tile)
        return;
    if (sfMouse_isButtonPressed(sfMouseLeft) ||
        sfJoystick_getAxisPosition(0, sfJoystickR) > 0) {
        if (weapon->weapon != PUNCH && sys->save->info->ammo == 0) {
            sfMusic_play(weapon->empty);
            return;
        }
        if (weapon->weapon != PUNCH)
            sys->save->info->ammo--;
        weapon->shot = time;
        sfMusic_play(weapon->info[weapon->weapon].sound);
        destroy_wall(sys->save->map, game->player, game);
    }
}

static void switch_scene(sfEvent event, state_info_t *state)
{
    if (is_input(event, sfKeyTab, sfTrue, 3)) {
        state->old_scene = state->scene;
        state->scene = PAUSE;
    }
}

static void show_fps(sfEvent event, toolbar_t *tool)
{
    if (is_input(event, sfKeyF4, sfTrue, 0)) {
        if (tool->fps == sfTrue)
            tool->fps = sfFalse;
        else
            tool->fps = sfTrue;
    }
}

static void save_game(sfEvent event, save_t *save, toolbar_t *tool)
{
    if (is_input(event, sfKeyF5, sfFalse, 0)) {
        save_map(save);
        tool->save = save->info->time;
    }
}

static void interact(int **map, player_t *player, system_t *sys)
{
    sfVector2i casted_pos = cast_pos(&player->center_ray.pos,
        player->center_ray.type);

    if (casted_pos.x < 0 || casted_pos.y < 0)
        return;
    if (sfKeyboard_isKeyPressed(sfKeyF)) {
        if (player->center_ray.distance < OPEN_DISTANCE &&
            map[casted_pos.y][casted_pos.x] == wall_textures[DOOR].value)
            map[casted_pos.y][casted_pos.x] = 0;
        if (player->center_ray.distance < FINISH_DISTANCE &&
            map[casted_pos.y][casted_pos.x] == wall_textures[FINAL].value)
            sys->state->scene = MENU;
    }
}

void game_events(system_t *sys, game_t *game)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        change_weapons(event, game, game->weapon);
        switch_scene(event, sys->state);
        show_fps(event, game->tool);
        save_game(event, sys->save, game->tool);
    }
    click(sys, game->weapon, game->time_info->time, game);
    interact(sys->save->map, game->player, sys);
    move_player(game->player, game->time_info->delta,
        &game->tool->head->rectangle.left);
    sfSprite_setTextureRect(game->tool->head->sprite,
        game->tool->head->rectangle);
}
