/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** handle_items
*/

#include "element.h"
#include "math.h"
#include "save.h"
#include "linked_list.h"

void item_weapon(int quantity, int *item, __maybe_unused int max)
{
    int tmp = pow(2, quantity);

    if (tmp & *item)
        return;
    *item += tmp;
}

void item_potion(int quantity, int *item, int max)
{
    *item += quantity;
    if (*item > max)
        *item = max;
}

static void handle_item(save_t *save, game_t *game, item_t *item)
{
    int value = 0;

    if (item->type < I_WEAPON_TWO) {
        value = save->info->item_info[ITEM[item->type].info];
        ITEM[item->type].func(ITEM[item->type].quantity,
            &value, ITEM[item->type].max);
        save->info->item_info[ITEM[item->type].info] = value;
    } else
        ITEM[item->type].func(item->type - I_FLASHLIGHT,
            &save->info->weapons, 0);
    if (item->type <= I_STAMINA)
        game->time_info->item = TIME_OVERLAY;
    else
        game->time_info->weapon = TIME_OVERLAY;
}

void handle_items(save_t *save, game_t *game)
{
    node_t *next = NULL;
    item_t *tmp = NULL;

    for (node_t *head = save->items->head; head != NULL; head = next) {
        next = head->next;
        tmp = head->data;
        if (tmp->dist > ITEM_RANGE)
            continue;
        handle_item(save, game, tmp);
        sfMusic_play(game->music[PICK_UP]);
        delete_node(save->items, head, &free);
    }
}
