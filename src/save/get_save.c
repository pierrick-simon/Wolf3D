/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** get_save
*/

#include "save.h"
#include "game.h"
#include "my.h"
#include "entities.h"
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

static int get_dup_info(char **tab, save_t *save, int offset)
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
    if (initiate_body(tab + COOR + offset, save) == ERROR) {
        free(save->name);
        return ERROR;
    }
    return SUCCESS;
}

static int initiate_struct(char **tab, save_t *save, int offset)
{
    save->size = (sfVector2i){atoi(tab[SIZE_X]), atoi(tab[SIZE_Y])};
    save->info->start_pos =
        (sfVector2f){atof(tab[START_X]), atof(tab[START_Y])};
    save->info->start_angle = atof(tab[START_ANGLE]);
    save->info->item_info[INFO_HEALTH] = atoi(tab[HEALTH]);
    save->info->item_info[INFO_FLASHLIGHT] = atoi(tab[FLASHLIGHT_INFO]);
    save->info->item_info[INFO_AMMO_PISTOL] = atoi(tab[AMMO_PISTOL]);
    save->info->item_info[INFO_AMMO_SHUTGUN] = atoi(tab[AMMO_SHUTGUN]);
    save->info->item_info[INFO_AMMO_MINIGUN] = atoi(tab[AMMO_MINIGUN]);
    save->info->item_info[INFO_AMMO_PLASMA] = atoi(tab[AMMO_PLASMA]);
    save->info->item_info[INFO_STAMINA] = atoi(tab[STAMINA]);
    save->info->score = atoi(tab[CURRENT_SCORE]);
    save->info->time = atoi(tab[TIME]) * SEC_IN_MICRO;
    save->info->weapons = atoi(tab[WEAPONS]);
    save->info->start_weapon = atoi(tab[START_WEAPON]);
    save->info->difficulty = atof(tab[DIFFICULTY_INFO]);
    return get_dup_info(tab, save, offset);
}

static int get_save_all(save_t *save, char **tab)
{
    int offset = 0;

    if (check_save(save, tab, &offset) == ERROR
        || initiate_struct(tab, save, offset) == ERROR
        || init_mini_map_color(save) == ERROR) {
        free_array(tab);
        destroy_save(save);
        return ERROR;
    }
    free_array(tab);
    if (check_start(save) == ERROR) {
        free_map(save->size.y, save->map);
        destroy_save(save);
        return ERROR;
    }
    return SUCCESS;
}

int get_save(char *file, save_t *save)
{
    char **tab = get_tab(file);

    destroy_save(save);
    save->init = sfFalse;
    if (tab == NULL)
        return ERROR;
    if (get_save_all(save, tab) == ERROR)
        return ERROR;
    save->init = sfTrue;
    save->update = sfFalse;
    return SUCCESS;
}
