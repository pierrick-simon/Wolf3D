/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** add_node_item
*/

#include "linked_list.h"
#include "save.h"
#include "my.h"

static int check_item(char **tab)
{
    if (is_int_float(tab[I_ID]) != NATURAL || atoi(tab[I_ID]) >= NB_ITEM)
        return ERROR;
    if (is_int_float(tab[I_POS_X]) == MY_NAN
        || is_int_float(tab[I_POS_Y]) == MY_NAN)
        return ERROR;
    if (is_int_float(tab[I_QUANTITY]) != NATURAL)
        return ERROR;
    return SUCCESS;
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
    item->id = atoi(tab[I_ID]);
    item->pos = (sfVector2f){atof(tab[I_POS_X]), atof(tab[I_POS_Y])};
    item->quantity = atoi(tab[I_QUANTITY]);
    push_to_tail(items, item);
    free_array(tab);
    return SUCCESS;
}
