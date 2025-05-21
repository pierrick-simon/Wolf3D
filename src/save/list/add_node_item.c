/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** add_node_item
*/

#include "linked_list.h"
#include "save.h"
#include "element.h"
#include "my.h"

static int check_item(char **tab)
{
    if (is_int_float(tab[I_TYPE]) != NATURAL || atoi(tab[I_TYPE]) >= NB_ITEM)
        return ERROR;
    if (is_int_float(tab[I_POS_X]) == MY_NAN
        || is_int_float(tab[I_POS_Y]) == MY_NAN)
        return ERROR;
    return SUCCESS;
}

static void fill_node_item(
    linked_list_t *items, item_t *item, char **tab)
{
    static int id = 0;

    item->id = id;
    item->type = atoi(tab[E_TYPE]);
    item->pos = (sfVector2f){atof(tab[I_POS_X]), atof(tab[I_POS_Y])};
    push_to_tail(items, item);
    id++;
}

int add_node_item(linked_list_t *items, char *line)
{
    char **tab = my_str_to_word_array(line, ":", "");
    item_t *item = NULL;

    if (tab == NULL)
        return ERROR;
    if (array_len(tab) != NB_STR_ITEM || check_item(tab) == ERROR) {
        free_array(tab);
        return ERROR;
    }
    item = malloc(sizeof(item_t));
    if (item == NULL) {
        free_array(tab);
        return ERROR;
    }
    fill_node_item(items, item, tab);
    free_array(tab);
    return SUCCESS;
}
