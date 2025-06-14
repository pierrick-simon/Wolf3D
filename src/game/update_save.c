/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** update_save
*/

#include "game.h"
#include "save.h"
#include <math.h>

static void update_save_weapon(system_t *sys, weapon_t *weapon)
{
    weapon->info[weapon->weapon].rectangle.left = 0;
    weapon->info[weapon->weapon].current_tile = 0;
    weapon->horizontal_offset = 0;
    weapon->shot = -1;
    weapon->weapon = (int)log2(sys->save->info->start_weapon);
    sfSprite_setTexture(weapon->sprite,
        weapon->info[weapon->weapon].texture, sfTrue);
    sfSprite_setTextureRect(weapon->sprite,
        weapon->info[weapon->weapon].rectangle);
    sfSprite_setOrigin(weapon->sprite,
    (sfVector2f){weapon->info[weapon->weapon].size.x / 2,
    weapon->info[weapon->weapon].size.y});
}

static void change_door(door_t *data, game_t *game, system_t *sys)
{
    data->state -= game->time_info->delta;
    if (data->state < 0.0)
        data->state = 0.0;
    if (data->state == 0.0)
        sys->save->map[data->pos.y][data->pos.x] = 0;
}

static void update_doors(system_t *sys, game_t *game)
{
    node_t *node = sys->save->doors->head;
    door_t *data = NULL;

    while (node != NULL) {
        data = (door_t *)node->data;
        if (data->activated == sfTrue &&
            sys->save->map[data->pos.y][data->pos.x] != 0) {
            change_door(data, game, sys);
        }
        node = node->next;
    }
}

static void update_save_light_continue(sfUint64 time, light_t *light)
{
    int cycle = ceil(time / SEC_IN_MICRO / MIN_IN_SEC);
    int sec = time / (SEC_IN_MICRO / NIGHT_NB) % (MIN_IN_SEC * NIGHT_NB);
    int tmp = sec - SMOOTH_OVERLAY;

    if (cycle % 2 != 0) {
        light->night_on = sfTrue;
        if (tmp > 0)
            sfRectangleShape_setFillColor(light->overlay,
                sfColor_fromRGBA(0, 0, 0, OVERLAY_MAX - (tmp * OVERLAY_STEP)));
        else
            sfRectangleShape_setFillColor(light->overlay,
                sfColor_fromRGBA(0, 0, 0, OVERLAY_MAX));
    } else {
        light->night_on = sfFalse;
        if (tmp > 0)
            sfRectangleShape_setFillColor(light->overlay,
                    sfColor_fromRGBA(0, 0, 0, tmp * OVERLAY_STEP));
        else
            sfRectangleShape_setFillColor(light->overlay, sfTransparent);
    }
}

static void update_save_light(
    system_t *sys, light_t *light, sprite_t *flashlight)
{
    light->flash_on = sfFalse;
    light->sec = 1;
    flashlight->rectangle.left = 0;
    sfSprite_setTextureRect(flashlight->sprite, flashlight->rectangle);
    sfRectangleShape_setFillColor(light->overlay,
                sfColor_fromRGBA(0, 0, 0, 0));
    if (sys->save->info->time == 0)
        light->night_on = sfFalse;
    else
        update_save_light_continue(sys->save->info->time, light);
}

static void update_health_enemi(linked_list_t *entities, float difficulty)
{
    entity_t *entity = NULL;

    for (node_t *head = entities->head; head != NULL; head = head->next) {
        entity = head->data;
        if (entity->health == 0 && entity->type >= NB_ITEM)
            entity->health = ENEMY[entity->type].health * difficulty;
    }
}

static void update_str(system_t *sys, draw_textbox_t *draw)
{
    if (sys->controler == sfTrue) {
        sprintf(draw[TOOL_INTERACT].str, "press (a) to interact");
    }
}

static void update_save_time(time_info_t *time)
{
    time->time = 0;
    time->item = 0;
    time->weapon = 0;
    time->shot = 0;
}

void update_save(system_t *sys, game_t *game)
{
    update_doors(sys, game);
    if (sys->save->update == sfFalse) {
        game->player->pos = sys->save->info->start_pos;
        game->player->angle = sys->save->info->start_angle;
        game->player->save = sys->save;
        game->tool->sprint = 0;
        game->tool->no_sprint = 0;
        game->tool->save = -1;
        game->tool->last_save = 0;
        update_str(sys, game->tool->draw);
        update_save_time(game->time_info);
        update_save_light(sys, game->light, game->tool->flashlight);
        update_save_weapon(sys, game->weapon);
        update_health_enemi(sys->save->entities, sys->save->info->difficulty);
        sys->save->update = sfTrue;
    }
    sys->save->info->start_pos = game->player->pos;
    sys->save->info->start_angle = game->player->angle;
}
