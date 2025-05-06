/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** save_score
*/

#include "save.h"
#include "score.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void save_score(save_t *save, char *name)
{
    char *tmp = malloc(sizeof(char) * (strlen(save->name) + SCORE_LEN));
    int fd = 0;

    if (tmp == NULL)
        return;
    sprintf(tmp, "score/%s.conf", save->name);
    fd = open(tmp, O_CREAT | O_WRONLY | O_APPEND, 0744);
    free(tmp);
    if (fd == -1)
        return;
    dprintf(fd, "\n%s:%d:%d",
        name, save->info->score, (int)(save->info->time / SEC_IN_MICRO));
    close(fd);
}
