/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_map
*/

#include "save.h"
#include "my.h"
#include <stdio.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static void check_save_map(char *name, select_map_t *map)
{
    char *tmp = NULL;
    int fd = 0;

    if (map->check == sfTrue || name == NULL)
        return;
    tmp = malloc(sizeof(char) * (strlen(name) + LEN_SAVE));
    if (tmp == NULL)
        return;
    map->check = sfTrue;
    sprintf(tmp, "save/%s.legend", name);
    fd = open(tmp, O_RDONLY);
    free(tmp);
    if (fd == -1) {
        map->save = sfFalse;
        map->draw[MAP_CONTINUE].color = GREY;
    } else {
        map->save = sfTrue;
        close(fd);
    }
}

void check_edit(system_t *sys, select_map_t *map)
{
    if (strcmp(sys->dir, "levels") == 0) {
        map->edit = sfFalse;
        map->draw[MAP_EDIT].color = GREY;
    } else {
        map->edit = sfTrue;
    }
}

void draw_map(system_t *sys, void *structure)
{
    select_map_t *map = (select_map_t *)structure;
    sfSoundStatus music = sfMusic_getStatus(sys->music);

    check_save_map(sys->save->name, map);
    check_edit(sys, map);
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    sprintf(map->draw[MAP_TITLE].str, "%*s",
        get_offset(sys->save->name, MAX_NAME), sys->save->name);
    for (int i = 0; i < NB_MAP; i++)
        draw_string(sys, sys->textbox, &map->draw[i]);
    if (sys->save->music != NULL)
        sfMusic_pause(sys->save->music);
    if (music == sfStopped || music == sfPaused)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
    map_events(sys, map);
}
