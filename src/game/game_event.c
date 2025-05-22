/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** event
*/

#include <math.h>
#include "save.h"
#include "game.h"
#include "entities.h"

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

static void switch_scene(sfEvent event, state_info_t *state)
{
    if (is_input(event, sfKeyEscape, sfTrue, 3)) {
        state->old_scene = state->scene;
        state->scene = PAUSE;
    }
}

static void tool_interact(
    sfEvent event, save_t *save, toolbar_t *tool, light_t *light)
{
    if (is_input(event, sfKeyF5, sfFalse, 0))
        tool->save = save->info->time;
    if (is_input(event, sfKeyF4, sfTrue, 0)) {
        if (tool->fps == sfTrue)
            tool->fps = sfFalse;
        else
            tool->fps = sfTrue;
    }
    if (is_input(event, sfKeyV, sfFalse, 0)) {
        if (light->flash_on == sfTrue)
            light->flash_on = sfFalse;
        else
            light->flash_on = sfTrue;
        move_rect(tool->flashlight->sprite, &tool->flashlight->rectangle,
            FLASHLIGHT_SPRITE_X, FLASHLIGHT_SPRITE_STATUS);
    }
}

static void open_door(system_t *sys, sfVector2i *pos)
{
    node_t *node = sys->save->doors->head;
    door_t *data = NULL;

    while (node != NULL) {
        data = (door_t *)node->data;
        if (data->pos.x == pos->x && data->pos.y == pos->y &&
            data->activated == sfFalse) {
            data->activated = sfTrue;
        }
        node = node->next;
    }
}

static void interact(int **map, player_t *player, system_t *sys, game_t *game)
{
    sfVector2i casted_pos = cast_pos(&player->center_ray.pos,
        player->center_ray.type);

    if (casted_pos.x < 0 || casted_pos.y < 0)
        return;
    if (sfKeyboard_isKeyPressed(sfKeyF)) {
        if (player->center_ray.distance < OPEN_DISTANCE &&
            map[casted_pos.y][casted_pos.x] == wall_textures[DOOR].value) {
            open_door(sys, &casted_pos);
            sfMusic_play(game->music[DOOR_MU]);
        }
        if (player->center_ray.distance < FINISH_DISTANCE &&
            map[casted_pos.y][casted_pos.x] == wall_textures[FINAL].value) {
            sys->state->scene = WIN;
            sfMusic_play(game->music[END_LEVEL]);
        }
    }
}

void game_events(system_t *sys, game_t *game)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        change_weapons(event, game, game->weapon);
        switch_scene(event, sys->state);
        tool_interact(event, sys->save, game->tool, game->light);
    }
    shot(sys, game->weapon, game);
    interact(sys->save->map, game->player, sys, game);
    move_player(game, game->time_info->delta,
        &game->tool->head->rectangle.left, game->music[FOOTSTEPS]);
    move_y(game->player, game->time_info->delta);
    sfSprite_setTextureRect(game->tool->head->sprite,
        game->tool->head->rectangle);
}
