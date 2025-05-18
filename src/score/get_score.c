/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** get_score
*/

#include "score.h"
#include "linked_list.h"
#include "my.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static char *get_time(int time, char **tab)
{
    int min = time / MIN_IN_SEC;
    int sec = time % MIN_IN_SEC;
    char *tmp = malloc(sizeof(char) * (get_nblen(min) + get_nblen(sec) + 2));

    if (tmp == NULL) {
        free_array(tab);
        return NULL;
    }
    sprintf(tmp, "%02d:%02d", min, sec);
    return tmp;
}

static void get_line(linked_list_t *list, char **tab)
{
    score_info_t *node = NULL;

    if (array_len(tab) != NB_S_LOAD)
        return;
    node = malloc(sizeof(score_info_t));
    if (node == NULL) {
        free_array(tab);
        return;
    }
    node->name = tab[LOAD_S_NAME];
    node->score = tab[LOAD_S_SCORE];
    node->time_sec = atoi(tab[LOAD_S_TIME]);
    node->time = get_time(node->time_sec, tab);
    if (node->time == NULL) {
        free(node);
        return;
    }
    free(tab[LOAD_S_TIME]);
    free(tab);
    push_to_head(list, node);
}

static void fill_list(linked_list_t *list, char **tab)
{
    char **tmp = NULL;

    for (int i = 0; tab[i] != NULL; i++) {
        tmp = my_str_to_word_array(tab[i], ":", "");
        if (tmp == NULL)
            continue;
        get_line(list, tmp);
    }
}

static int get_tab_score(char *name, char ***tab)
{
    char *tmp = malloc(sizeof(char) * (strlen(name) + SCORE_LEN));

    if (tmp == NULL)
        return ERROR;
    sprintf(tmp, "score/%s.conf", name);
    *tab = get_tab(tmp);
    free(tmp);
    if (*tab == NULL)
        return ERROR;
    return SUCCESS;
}

linked_list_t *get_score(char *name)
{
    linked_list_t *list = initialize_linked_list();
    char **tab = NULL;

    if (list == NULL)
        return NULL;
    if (get_tab_score(name, &tab) == ERROR)
        return list;
    fill_list(list, tab);
    free_array(tab);
    return list;
}
