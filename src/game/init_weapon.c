/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_weapon
*/

#include "game.h"
#include "my.h"
#include <stdlib.h>

static int init_weapon(char *info, weapon_info_t *weapon)
{
    char **tab = my_str_to_word_array(info, ":", "");

    weapon->texture = NULL;
    weapon->sound = NULL;
    if (tab == NULL)
        return ERROR;
    if (array_len(tab) != 6) {
        free_array(tab);
        return ERROR;
    }
    weapon->texture = sfTexture_createFromFile(tab[0], NULL);
    weapon->sound = sfMusic_createFromFile(tab[1]);
    weapon->size = (sfVector2f){atoi(tab[2]), atoi(tab[3])};
    weapon->nb_tile = atoi(tab[4]);
    weapon->speed = atof(tab[5]);
    weapon->size.x /= weapon->nb_tile;
    weapon->rectangle = (sfIntRect){0, 0, weapon->size.x, weapon->size.y};
    weapon->current_tile = 0;
    weapon->posf = (sfVector2f){WIN_WIDTH / 2, TOOLBAR_POS};
    return SUCCESS;
}

static int get_weapon_info(weapon_info_t *info)
{
    char **tab = get_tab("config_file/weapon.conf");
    int return_value = SUCCESS;

    if (tab == NULL)
        return ERROR;
    for (int i = 0; i < NB_WEAPON; i++) {
        if (init_weapon(tab[i], &info[i]) == ERROR)
            return_value = ERROR;
    }
    free_array(tab);
    return return_value;
}

int init_weapons(weapon_t *weapon)
{
    *weapon = (weapon_t){NULL};
    weapon->shot = SEC_IN_MICRO * -1;
    weapon->weapon = 0;
    weapon->sprite = sfSprite_create();
    weapon->info = malloc(sizeof(weapon_info_t) * NB_WEAPON);
    weapon->empty = sfMusic_createFromFile("asset/empty.ogg");
    if (weapon->sprite == NULL || weapon->info == NULL
        || get_weapon_info(weapon->info) == ERROR)
        return ERROR;
    sfSprite_setOrigin(weapon->sprite,
        (sfVector2f){weapon->info[0].size.x / 2, weapon->info[0].size.y});
    sfSprite_setTexture(weapon->sprite, weapon->info[0].texture, sfTrue);
    sfSprite_setTextureRect(weapon->sprite, weapon->info[0].rectangle);
    sfSprite_setScale(weapon->sprite, (sfVector2f){2, 2});
    sfSprite_setPosition(weapon->sprite, weapon->info[0].posf);
    return SUCCESS;
}
