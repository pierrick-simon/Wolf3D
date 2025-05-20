/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** add_node_enemie
*/

#include "save.h"
#include "linked_list.h"
#include "my.h"

static int check_enemie(char **tab)
{
    if (is_int_float(tab[E_TYPE]) != NATURAL || atoi(tab[E_TYPE]) >= NB_ENEMIE)
        return ERROR;
    if (is_int_float(tab[E_POS_X]) == MY_NAN
        || is_int_float(tab[E_POS_Y]) == MY_NAN)
        return ERROR;
    if (is_int_float(tab[E_HEALTH]) != NATURAL)
        return ERROR;
    return SUCCESS;
}

static void fill_node_enemie(
    linked_list_t *enemies, enemie_t *enemie, char **tab)
{
    static int id = 0;

    enemie->id = id;
    enemie->type = atoi(tab[E_TYPE]);
    enemie->pos = (sfVector2f){atof(tab[E_POS_X]), atof(tab[E_POS_Y])};
    enemie->health = atoi(tab[E_HEALTH]);
    enemie->cooldown = 0;
    enemie->dist = 0;
    push_to_tail(enemies, enemie);
    id++;
}

int add_node_enemie(linked_list_t *enemies, char *line)
{
    char **tab = my_str_to_word_array(line, ":", "");
    enemie_t *enemie = NULL;

    if (tab == NULL)
        return ERROR;
    if (array_len(tab) != NB_STR_ENEMIE || check_enemie(tab) == ERROR) {
        free_array(tab);
        return ERROR;
    }
    enemie = malloc(sizeof(enemie_t));
    if (enemie == NULL) {
        free_array(tab);
        return ERROR;
    }
    fill_node_enemie(enemies, enemie, tab);
    free_array(tab);
    return SUCCESS;
}
