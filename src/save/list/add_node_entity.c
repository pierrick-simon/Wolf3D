/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** add_node_entity
*/

#include "save.h"
#include "linked_list.h"
#include "entities.h"
#include "my.h"

static int check_entity(char **tab)
{
    if (is_int_float(tab[E_TYPE]) != NATURAL
        || atoi(tab[E_TYPE]) >= NB_ENTITIES)
        return ERROR;
    if (is_int_float(tab[E_POS_X]) == MY_NAN
        || is_int_float(tab[E_POS_Y]) == MY_NAN)
        return ERROR;
    if (is_int_float(tab[E_INFO]) != NATURAL)
        return ERROR;
    return SUCCESS;
}

static void fill_node_entity(
    linked_list_t *enemies, entity_t *entity, char **tab)
{
    entity->id = atoi(tab[E_TYPE]);
    entity->pos = (sfVector2f){atof(tab[E_POS_X]), atof(tab[E_POS_Y])};
    entity->health = atoi(tab[E_INFO]);
    entity->cooldown = 0;
    entity->dist = ITEM_RANGE * 2;
    push_to_tail(enemies, entity);
}

int add_node_entity(linked_list_t *enemies, char *line)
{
    char **tab = my_str_to_word_array(line, ":", "");
    entity_t *entity = NULL;

    if (tab == NULL)
        return ERROR;
    if (array_len(tab) != NB_STR_ENTITIES || check_entity(tab) == ERROR) {
        free_array(tab);
        return ERROR;
    }
    entity = malloc(sizeof(entity_t));
    if (entity == NULL) {
        free_array(tab);
        return ERROR;
    }
    fill_node_entity(enemies, entity, tab);
    free_array(tab);
    return SUCCESS;
}
