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

void handle_items(save_t *save)
{
    node_t *next = NULL;
    item_t *tmp = NULL;
    int value = 0;

    for (node_t *head = save->items->head; head != NULL; head = next) {
        next = head->next;
        tmp = head->data;
        if (tmp->dist > ITEM_RANGE)
            continue;
        if (tmp->type < I_WEAPON_TWO) {
            value = save->info->item_info[ITEM[tmp->type].info];
            ITEM[tmp->type].func(ITEM[tmp->type].quantity,
                &value, ITEM[tmp->type].max);
            save->info->item_info[ITEM[tmp->type].info] = value;
        } else
            ITEM[tmp->type].func(tmp->type - I_FLASHLIGHT,
                &save->info->weapons, 0);
        delete_node(save->items, head, &free);
    }
}
