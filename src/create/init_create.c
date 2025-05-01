/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** init_create
*/

#include "create.h"
#include <stdlib.h>

static int init_strings(char **strings, int *len_strings)
{
    len_strings[NAME] = MAX_NAME;
    len_strings[SIZE_X] = MAX_STRLEN;
    len_strings[SIZE_Y] = MAX_STRLEN;
    len_strings[POS_X] = MAX_STRLEN_POS;
    len_strings[POS_Y] = MAX_STRLEN_POS;
    len_strings[ANGLE] = MAX_STRLEN;
    for (int i = 0; i < NB_TEXTBOX; i++) {
        strings[i] = malloc(sizeof(char) * (len_strings[i] + 1));
        if (strings[i] == NULL)
            return ERROR;
        for (int j = 0; j < len_strings[i] + 1; j++)
            strings[i][j] = '\0';
    }
    strings[NB_TEXTBOX] = NULL;
    return SUCCESS;
}

void *init_create(void)
{
    create_t *create = malloc(sizeof(create_t));

    if (create == NULL)
        return NULL;
    create->str = 0;
    create->draw = init_from_conf("config_file/create.conf");
    if (create->draw == NULL)
        return NULL;
    for (int i = 0; i < NB_CREATE; i++)
        create->draw[i].color = sfBlack;
    create->len_strings = malloc(sizeof(char *) * (NB_TEXTBOX));
    create->strings = malloc(sizeof(char *) * (NB_TEXTBOX + 1));
    if (create->len_strings == NULL || create->strings == NULL
        || init_strings(create->strings, create->len_strings) == ERROR)
        return NULL;
    return (void *)create;
}
