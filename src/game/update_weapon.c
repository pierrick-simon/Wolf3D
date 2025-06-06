/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** update_weapon
*/

#include "game.h"
#include "save.h"
#include <stdio.h>
#include <math.h>

static void update_inbag(weapon_t *weapon, toolbar_t *tool, int bag)
{
    for (int i = 1; i < NB_WEAPON; i++) {
        if (((int)pow(2, i) & bag) == 0) {
            tool->draw[i + TOOL_TWO - 1].color = GREY;
            weapon->info[i].bag = sfFalse;
        } else {
            tool->draw[i + TOOL_TWO - 1].color = sfWhite;
            weapon->info[i].bag = sfTrue;
        }
    }
}

static void update_guns_movement(
    weapon_t *weapon, toolbar_t *tool, time_info_t *time)
{
    int ind = weapon->weapon;

    if ((tool->head->rectangle.left == 0
        && weapon->horizontal_offset < MAX_WIDTH)
        || (tool->head->rectangle.left == HEAD_SPRITE_X
        && weapon->horizontal_offset < 0))
        weapon->horizontal_offset += (double)time->delta * MIN_IN_SEC;
    else if ((tool->head->rectangle.left == HEAD_SPRITE_X * 2
        && weapon->horizontal_offset > MAX_WIDTH * SKIP)
        || (tool->head->rectangle.left == HEAD_SPRITE_X
        && weapon->horizontal_offset > 0))
        weapon->horizontal_offset -= (double)time->delta * MIN_IN_SEC;
    sfSprite_setPosition(weapon->sprite, (sfVector2f){weapon->info[ind].posf.x
        + weapon->horizontal_offset, weapon->info[ind].posf.y
        + (cos((double)(time->time / (SEC_IN_MICRO
        / MOV_OFFSET_GUN))) * MOV_OFFSET_GUN) + MOV_OFFSET_GUN});
}

static void update_guns(weapon_t *weapon, toolbar_t *tool, int bag)
{
    int ind = weapon->weapon;

    update_inbag(weapon, tool, bag);
    if (weapon->weapon != PUNCH)
        tool->draw[weapon->weapon + TOOL_TWO - 1].color = sfRed;
    if (weapon->info[ind].current_tile == weapon->info[ind].nb_tile)
        weapon->info[ind].current_tile = 0;
    if (ind == PUNCH) {
        if (weapon->info[ind].current_tile == 0)
            weapon->info[ind].posf.x = HAND_POS;
        else
            weapon->info[ind].posf.x = PUNCH_POS;
    }
}

void shot_gun_anim(weapon_t *weapon,
    time_info_t *time, toolbar_t *tool, int bag)
{
    double diff = (double)(time->time - weapon->shot) / SEC_IN_MICRO;
    int ind = weapon->weapon;

    for (int i = 0; i < weapon->info[ind].nb_tile; i++) {
        if (weapon->shot == -1)
            break;
        if (diff > weapon->info[ind].speed * i
            && diff < weapon->info[ind].speed * (i + 1)
            && weapon->info[ind].current_tile == i) {
            move_rect(weapon->sprite, &weapon->info[ind].rectangle,
                weapon->info[ind].size.x, weapon->info[ind].nb_tile);
            weapon->info[ind].current_tile++;
            break;
        }
    }
    update_guns(weapon, tool, bag);
    update_guns_movement(weapon, tool, time);
}

void update_ammo(system_t *sys, game_t *game)
{
    if (game->weapon->weapon == PUNCH) {
        game->tool->draw[TOOL_AMMO_NB].color = sfWhite;
        sprintf(game->tool->draw[TOOL_AMMO_NB].str, " INF");
    } else
        update_toolbar_percent(&game->tool->draw[TOOL_AMMO_NB],
            sys->save->info->item_info[game->weapon->weapon]);
}

static sfBool is_boss(linked_list_t *entities)
{
    for (node_t *head = entities->head; head != NULL; head = head->next) {
        if (((entity_t *)head->data)->type == E_BOSS)
            return sfTrue;
    }
    return sfFalse;
}

void update_interact(toolbar_t *tool, player_t *player, int **map)
{
    sfVector2i casted_pos = cast_pos(&player->center_ray.pos,
        player->center_ray.type);

    tool->interact = sfFalse;
    tool->finish = sfTrue;
    if (casted_pos.x < 0 || casted_pos.y < 0)
        return;
    if (player->center_ray.distance < OPEN_DISTANCE &&
        map[casted_pos.y][casted_pos.x] == wall_textures[DOOR].value)
        tool->interact = sfTrue;
    if ((player->center_ray.distance < FINISH_DISTANCE &&
        map[casted_pos.y][casted_pos.x] == wall_textures[FINAL].value)) {
        tool->interact = sfTrue;
        if (is_boss(player->save->entities) == sfTrue)
            tool->finish = sfFalse;
    }
    if (tool->finish == sfFalse)
        tool->draw[TOOL_INTERACT].color = GREY;
    else
        tool->draw[TOOL_INTERACT].color = sfWhite;
}
