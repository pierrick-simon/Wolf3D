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
    for (int i = 0; i < NB_WEAPON; i++) {
        if (((int)pow(2, i) & bag) == 0) {
            tool->draw[i + TOOL_ONE].color = GREY;
            weapon->info[i].bag = sfFalse;
        } else {
            tool->draw[i + TOOL_ONE].color = sfWhite;
            weapon->info[i].bag = sfTrue;
        }
    }
}

static void update_guns(weapon_t *weapon, toolbar_t *tool, int bag)
{
    int ind = weapon->weapon;

    update_inbag(weapon, tool, bag);
    tool->draw[weapon->weapon + TOOL_ONE].color = sfRed;
    if (weapon->info[ind].current_tile == weapon->info[ind].nb_tile)
        weapon->info[ind].current_tile = 0;
    if (ind == PUNCH) {
        if (weapon->info[ind].current_tile == 0)
            weapon->info[ind].posf.x = HAND_POS;
        else
            weapon->info[ind].posf.x = PUNCH_POS;
    }
    sfSprite_setPosition(weapon->sprite, weapon->info[ind].posf);
}

void shot_gun_anim(weapon_t *weapon, sfInt64 time, toolbar_t *tool, int bag)
{
    double diff = (double)(time - weapon->shot) / SEC_IN_MICRO;
    int ind = weapon->weapon;

    for (int i = 0; i < weapon->info[ind].nb_tile; i++) {
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
}
