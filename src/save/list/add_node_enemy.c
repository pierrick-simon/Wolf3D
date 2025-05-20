/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** add_node_enemy
*/

#include "save.h"
#include "linked_list.h"
#include "element.h"
#include "my.h"

static int check_enemy(char **tab)
{
    if (is_int_float(tab[E_TYPE]) != NATURAL || atoi(tab[E_TYPE]) >= NB_ENEMY)
        return ERROR;
    if (is_int_float(tab[E_POS_X]) == MY_NAN
        || is_int_float(tab[E_POS_Y]) == MY_NAN)
        return ERROR;
    if (is_int_float(tab[E_HEALTH]) != NATURAL)
        return ERROR;
    return SUCCESS;
}

static void fill_node_enemy(
    linked_list_t *enemys, enemy_t *enemy, char **tab)
{
    static int id = 0;

    enemy->id = id;
    enemy->type = atoi(tab[E_TYPE]);
    enemy->pos = (sfVector2f){atof(tab[E_POS_X]), atof(tab[E_POS_Y])};
    enemy->health = atoi(tab[E_HEALTH]);
    enemy->cooldown = 0;
    push_to_tail(enemys, enemy);
    id++;
}

int add_node_enemy(linked_list_t *enemys, char *line)
{
    char **tab = my_str_to_word_array(line, ":", "");
    enemy_t *enemy = NULL;

    if (tab == NULL)
        return ERROR;
    if (array_len(tab) != NB_STR_ENEMY || check_enemy(tab) == ERROR) {
        free_array(tab);
        return ERROR;
    }
    enemy = malloc(sizeof(enemy_t));
    if (enemy == NULL) {
        free_array(tab);
        return ERROR;
    }
    fill_node_enemy(enemys, enemy, tab);
    free_array(tab);
    return SUCCESS;
}
