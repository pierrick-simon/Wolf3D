/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** destroy_create
*/
//vivikaka
#include "create.h"
#include "my.h"
#include <stdlib.h>
void destroy_create(void *structure)
{
    create_t *create = (create_t *)structure;

    if (create->draw != NULL)
        free_draw_textbox(create->draw, -1);
    if (create->strings != NULL)
        free_array(create->strings);
    if (create->len_strings != NULL)
        free(create->len_strings);
    free(create);
}
