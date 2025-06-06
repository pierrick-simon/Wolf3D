/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** save_map
*/

#include "save.h"
#include "linked_list.h"
#include "entities.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static void write_entities(save_t *save, int fd)
{
    node_t *head = save->entities->head;
    entity_t *tmp = NULL;

    dprintf(fd, "%d\n", get_list_len(save->entities));
    while (head != NULL) {
        tmp = head->data;
        dprintf(fd, "%d:%f:%f:%d\n",
            tmp->type, tmp->pos.x, tmp->pos.y, tmp->health);
        head = head->next;
    }
}

static void write_header(save_t *save, int fd)
{
    dprintf(fd, "%s\n%d\n%d\n%f\n%f\n%f\n%.0f\n"
        "%.0f\n%.0f\n%.0f\n%.0f\n%.0f\n%.0f\n%d\n%d\n%d\n%d\n%f\n%s\n",
        save->name, save->size.x, save->size.y, save->info->start_pos.x,
        save->info->start_pos.y, save->info->start_angle,
        save->info->item_info[INFO_HEALTH],
        save->info->item_info[INFO_FLASHLIGHT],
        save->info->item_info[INFO_AMMO_PISTOL],
        save->info->item_info[INFO_AMMO_SHUTGUN],
        save->info->item_info[INFO_AMMO_MINIGUN],
        save->info->item_info[INFO_AMMO_PLASMA],
        save->info->item_info[INFO_STAMINA],
        save->info->score, (int)save->info->time / SEC_IN_MICRO,
        save->info->weapons, save->info->start_weapon,
        save->info->difficulty, save->music_path);
}

static void write_body(save_t *save, int fd)
{
    for (int i = 0; i < save->size.y; i++) {
        for (int j = 0; j < save->size.x; j++)
            dprintf(fd, "%d ", save->map[i][j]);
        dprintf(fd, "\n");
    }
}

void save_map(save_t *save, char *dir)
{
    char *tmp = malloc(sizeof(char) *
        (strlen(save->name) + LEN_SAVE + strlen(dir)));
    int fd = 0;

    if (tmp == NULL)
        return;
    sprintf(tmp, "%s/%s.legend", dir, save->name);
    fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0744);
    free(tmp);
    if (fd == -1)
        return;
    write_header(save, fd);
    write_entities(save, fd);
    write_body(save, fd);
    close(fd);
}
