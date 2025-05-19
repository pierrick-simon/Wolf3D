/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** get_save
*/

#include "save.h"
#include "game.h"
#include "my.h"
#include <stdlib.h>
#include <string.h>

static void add_value(save_t *save, int i, int j, int nb)
{
    door_t *data = NULL;

    save->map[i][j] = nb;
    if (save->map[i][j] == wall_textures[DOOR].value) {
        data = malloc(sizeof(door_t));
        if (data == NULL)
            return;
        data->pos = (sfVector2i){j, i};
        data->state = 1.0;
        data->activated = sfFalse;
        push_to_head(save->doors, data);
    }
}

static int initiate_body(char **tab, save_t *save)
{
    char *line = NULL;
    char *nb = NULL;

    save->map = malloc(sizeof(int *) * (save->size.y));
    if (save->map == NULL)
        return ERROR;
    for (int i = 0; i < save->size.y; i++) {
        save->map[i] = malloc(sizeof(int) * save->size.x);
        if (save->map[i] == NULL) {
            free_map(i, save->map);
            return ERROR;
        }
        line = tab[i];
        nb = strtok(line, " ");
        for (int j = 0; nb != NULL; j++) {
            add_value(save, i, j, atoi(nb));
            nb = strtok(NULL, " ");
        }
    }
    return SUCCESS;
}

static int get_dup_info(char **tab, save_t *save)
{
    save->name = strdup(tab[NAME]);
    if (save->name == NULL)
        return ERROR;
    save->music_path = strdup(tab[MUSIC]);
    if (save->music_path == NULL)
        return ERROR;
    save->music = sfMusic_createFromFile(tab[MUSIC]);
    if (save->music_path == NULL)
        return ERROR;
    save->doors = initialize_linked_list();
    if (save->doors == NULL || initiate_body(tab + COOR, save) == ERROR) {
        free(save->name);
        return ERROR;
    }
    return SUCCESS;
}

static int initiate_struct(char **tab, save_t *save)
{
    save->size = (sfVector2i){atoi(tab[SIZE_X]), atoi(tab[SIZE_Y])};
    save->info->start_pos =
        (sfVector2f){atof(tab[START_X]), atof(tab[START_Y])};
    save->info->start_angle = atof(tab[START_ANGLE]);
    save->info->health = atoi(tab[HEALTH]);
    save->info->flashlight = atoi(tab[FLASHLIGHT_INFO]);
    save->info->ammo = atoi(tab[AMMO]);
    save->info->stamina = atoi(tab[STAMINA]);
    save->info->score = atoi(tab[CURRENT_SCORE]);
    save->info->time = atoi(tab[TIME]) * SEC_IN_MICRO;
    save->info->weapons = atoi(tab[WEAPONS]);
    save->info->start_weapon = atoi(tab[START_WEAPON]);
    return get_dup_info(tab, save);
}

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

static int check_save(char **tab)
{
    int x = 0;
    int y = 0;

    if (array_len(tab) < COOR || check_header(tab, &x, &y) == ERROR
        || check_body(tab + COOR, x, y) == ERROR)
        return ERROR;
    return SUCCESS;
}

static int check_start(save_t *save)
{
    int x = save->info->start_pos.x / TILE_SIZE;
    int y = save->info->start_pos.y / TILE_SIZE;

    if (save->size.x * TILE_SIZE < save->info->start_pos.x
        || save->size.y * TILE_SIZE < save->info->start_pos.y
        || save->map[y][x] != 0)
            return ERROR;
    if (save->info->health > MAX_HEALTH)
        save->info->health = MAX_HEALTH;
    if (save->info->flashlight > MAX_HEALTH)
        save->info->flashlight = MAX_HEALTH;
    return SUCCESS;
}

int get_save(char *file, save_t *save)
{
    char **tab = get_tab(file);

    destroy_save(save);
    save->init = sfFalse;
    if (tab == NULL)
        return ERROR;
    if (check_save(tab) == ERROR || initiate_struct(tab, save) == ERROR
        || init_mini_map_color(save) == ERROR) {
        free_array(tab);
        return ERROR;
    }
    free_array(tab);
    if (check_start(save) == ERROR) {
        free_map(save->size.y, save->map);
        free(save->name);
        return ERROR;
    }
    save->init = sfTrue;
    save->update = sfFalse;
    return SUCCESS;
}
