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

static void check_save(char *name, select_map_t *map)
{
    char *tmp = NULL;
    int fd = 0;

    if (map->check == sfTrue)
        return;
    tmp = malloc(sizeof(char) * (strlen(name) + LEN_SAVE));
    if (tmp == NULL)
        return;
    map->check = sfTrue;
    sprintf(tmp, "save/%s.legend", name);
    fd = open(tmp, O_RDONLY);
    free(tmp);
    if (fd == -1)
        map->save = sfFalse;
    else {
        map->save = sfTrue;
        close(fd);
    }
}

void draw_map(system_t *sys, void *structure)
{
    select_map_t *map = (select_map_t *)structure;

    check_save(sys->save->name, map);
    sfRenderWindow_clear(sys->window, sfWhite);
    draw_background(sys, sys->background);
    sprintf(map->draw[MAP_TITLE].str, "%*s",
        get_offset(sys->save->name, MAX_NAME), sys->save->name);
    for (int i = 0; i < NB_MAP; i++)
        draw_string(sys, sys->textbox, &map->draw[i]);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    sfRenderWindow_display(sys->window);
    map_events(sys, map);
}
