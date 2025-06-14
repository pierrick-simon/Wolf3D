/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** check_save
*/

#include "save.h"
#include "my.h"
#include "linked_list.h"
#include "entities.h"
#include <stdlib.h>
#include <string.h>

static int check_header(char **tab, int *x, int *y)
{
    for (int i = 0; CHECK[i].check != NULL; i++) {
        if (CHECK[i].check(tab[i]) == ERROR)
            return ERROR;
    }
    *x = atoi(tab[SIZE_X]);
    *y = atoi(tab[SIZE_Y]);
    return SUCCESS;
}

static int check_line(char *line, int x)
{
    int count = 0;
    char *height = strtok(line, " ");

    while (height != NULL) {
        if (count > x)
            return ERROR;
        if (is_int_float(height) >= RATIONAL)
            return ERROR;
        count++;
        height = strtok(NULL, " ");
    }
    if (count < x)
        return ERROR;
    return SUCCESS;
}

static int check_body(char **tab, int x, int y)
{
    int i = 0;
    char *line = 0;

    while (tab[i] != NULL) {
        if (i > y)
            return ERROR;
        line = strdup(tab[i]);
        if (line == NULL)
            return ERROR;
        if (check_line(line, x) == ERROR) {
            free(line);
            return ERROR;
        }
        free(line);
        i++;
    }
    if (i < y)
        return ERROR;
    return SUCCESS;
}

static int check_entities(
    linked_list_t *list, char **tab, int *offset)
{
    int nb = 0;

    if (is_int_float(*tab) != NATURAL)
        return ERROR;
    nb = atoi(*tab);
    for (int i = 1; i <= nb; i++) {
        if (tab[i] == NULL
            || add_node_entity(list, tab[i]) == ERROR)
            return ERROR;
    }
    *offset += nb;
    return SUCCESS;
}

int check_save(save_t *save, char **tab, int *offset)
{
    int x = 0;
    int y = 0;

    if (array_len(tab) < COOR || check_header(tab, &x, &y) == ERROR
        || check_entities(save->entities, tab + ENTITIES, offset) == ERROR
        || check_body(tab + COOR + *offset, x, y) == ERROR)
        return ERROR;
    return SUCCESS;
}

static void pass_entities(linked_list_t *list, save_t *save)
{
    node_t *head = list->head;
    node_t *next = NULL;
    entity_t *tmp = NULL;
    int tile_x = 0;
    int tile_y = 0;

    while (head != NULL) {
        tmp = head->data;
        next = head->next;
        tile_x = tmp->pos.x / TILE_SIZE;
        tile_y = tmp->pos.y / TILE_SIZE;
        if (tile_x >= save->size.x || tile_y >= save->size.y
            || save->map[tile_y][tile_x] != 0)
            delete_node(list, head, &free);
        head = next;
    }
}

static void check_item_info(save_t *save)
{
    if (save->info->item_info[INFO_HEALTH] > MAX_HEALTH)
        save->info->item_info[INFO_HEALTH] = MAX_HEALTH;
    if (save->info->item_info[INFO_STAMINA] > MAX_HEALTH)
        save->info->item_info[INFO_STAMINA] = MAX_HEALTH;
    if (save->info->item_info[INFO_FLASHLIGHT] > MAX_HEALTH)
        save->info->item_info[INFO_FLASHLIGHT] = MAX_HEALTH;
    if (save->info->item_info[INFO_AMMO_PISTOL] > MAX_AMMO)
        save->info->item_info[INFO_AMMO_PISTOL] = MAX_AMMO;
    if (save->info->item_info[INFO_AMMO_SHUTGUN] > MAX_AMMO)
        save->info->item_info[INFO_AMMO_SHUTGUN] = MAX_AMMO;
    if (save->info->item_info[INFO_AMMO_MINIGUN] > MAX_AMMO)
        save->info->item_info[INFO_AMMO_MINIGUN] = MAX_AMMO;
}

int check_start(save_t *save)
{
    int x = save->info->start_pos.x / TILE_SIZE;
    int y = save->info->start_pos.y / TILE_SIZE;

    if (save->size.x * TILE_SIZE < save->info->start_pos.x
        || save->size.y * TILE_SIZE < save->info->start_pos.y
        || save->map[y][x] != 0)
            return ERROR;
    check_item_info(save);
    pass_entities(save->entities, save);
    return SUCCESS;
}
