/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** save_map
*/

#include "save.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static void write_header(save_t *save, int fd)
{
    dprintf(fd, "%s\n%d\n%d\n%f\n%f\n%f\n%d\n"
        "%.0f\n%d\n%d\n%d\n%d\n%d\n%d\n%s\n",
        save->name, save->size.x, save->size.y, save->info->start_pos.x,
        save->info->start_pos.y, save->info->start_angle, save->info->health,
        save->info->flashlight, save->info->ammo, save->info->stamina,
        save->info->score, (int)save->info->time / SEC_IN_MICRO,
        save->info->weapons, save->info->start_weapon, save->music_path);
}

static void write_body(save_t *save, int fd)
{
    for (int i = 0; i < save->size.y; i++) {
        for (int j = 0; j < save->size.x; j++)
            dprintf(fd, "%d ", save->map[i][j]);
        dprintf(fd, "\n");
    }
}

void save_map(save_t *save)
{
    char *tmp = malloc(sizeof(char) * (strlen(save->name) + LEN_SAVE));
    int fd = 0;

    if (tmp == NULL)
        return;
    sprintf(tmp, "save/%s.legend", save->name);
    fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0744);
    free(tmp);
    if (fd == -1)
        return;
    write_header(save, fd);
    write_body(save, fd);
    close(fd);
}
