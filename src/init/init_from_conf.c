/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_from_conf
*/

#include "wolf.h"
#include "my.h"
#include <stdlib.h>
#include <string.h>

static char **get_tab(char *path)
{
    char *tmp = open_file(path);
    char **tab = NULL;

    if (tmp == NULL)
        return NULL;
    tab = my_str_to_word_array(tmp, "\n", "");
    free(tmp);
    return tab;
}

static int get_scene(char *scene)
{
    for (int i = 0; i <= QUIT; i++) {
        if (strcmp(str_scene[i], scene) == 0)
            return i;
    }
    return MENU;
}

static int parse_conf(draw_textbox_t *draw, char **tab, int i)
{
    char **line = my_str_to_word_array(tab[i], ":", "");
    double x = 0;
    double y = 0;

    if (line == NULL)
        return ERROR;
    draw[i].str = strdup(line[0]);
    if (draw[i].str == NULL) {
        free_array(line);
        return ERROR;
    }
    x = WIN_WIDTH * atof(line[1]) + atof(line[2]);
    y = WIN_HEIGHT * atof(line[3]) + atof(line[4]);
    draw[i].pos = (sfVector2f){x, y};
    draw[i].size = atoi(line[5]);
    draw[i].scene = get_scene(line[6]);
    draw[i].color = sfWhite;
    free_array(line);
    return SUCCESS;
}

static int fill_draw(draw_textbox_t *draw, char **tab, int len)
{
    for (int i = 0; i < len; i++) {
        if (parse_conf(draw, tab, i) == ERROR) {
            free_draw_textbox(draw, i);
            free_array(tab);
            return ERROR;
        }
    }
    draw[len].str = NULL;
    return SUCCESS;
}

draw_textbox_t *init_from_conf(char *path)
{
    char **tab = get_tab(path);
    int len = 0;
    draw_textbox_t *draw = NULL;

    if (tab == NULL)
        return NULL;
    len = array_len(tab);
    draw = malloc(sizeof(draw_textbox_t) * (len + 1));
    if (draw == NULL) {
        free_array(tab);
        return NULL;
    }
    if (fill_draw(draw, tab, len) == ERROR)
        return NULL;
    free_array(tab);
    return draw;
}
