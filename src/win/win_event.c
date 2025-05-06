/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "quit.h"
#include "save.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int load_restart(win_t *win, system_t *sys, char *name)
{
    char *tmp = NULL;
    int exit = SUCCESS;

    if (win->str != WIN_RESTART)
        return SUCCESS;
    tmp = malloc(sizeof(char) * (strlen(name) + LEN_SAVE));
    if (tmp == NULL)
        return ERROR;
    sprintf(tmp, "maps/%s.legend", name);
    exit = get_save(tmp, sys->save);
    free(tmp);
    return exit;
}

static void update_score(system_t *sys, char *str)
{
    for (int i = 0; i < MAX_NAME_SCORE; i++) {
        if (str[i] == '\0')
            str[i] = '-';
    }
    save_score(sys->save, str);
    for (int i = 0; i < MAX_NAME_SCORE; i++)
        str[i] = '\0';
}

static void switch_scene(
    sfEvent event, system_t *sys, win_t *win, state_info_t *state)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0)) {
        update_score(sys, win->name);
        state->old_scene = state->scene;
        if (load_restart(win, sys, sys->save->name) == ERROR)
            state->scene = MAPS;
        else
            state->scene = win->draw[win->str].scene;
        state->scene = win->draw[win->str].scene;
        win->draw[win->str].color = sfWhite;
        win->str = WIN_ENTER;
    }
}

static void text_textbox(sfEvent event, char *str)
{
    int len = strlen(str);

    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeyBackspace && len > 0)
            str[len - 1] = '\0';
        if (event.key.code >= sfKeyA && event.key.code <= sfKeyZ
            && len < MAX_NAME_SCORE) {
            str[len] = event.key.code + 'A' - sfKeyA;
            str[len + 1] = '\0';
        }
    }
}

static void switch_str(sfEvent event, win_t *win)
{
    win->draw[win->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK)
        win->str--;
    if (is_input(event, sfKeyDown, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK)
        win->str++;
    if (win->str == NB_WIN)
        win->str = WIN_ENTER;
    if (win->str == WIN_SCORE)
        win->str = WIN_MENU;
    win->draw[win->str].color = sfRed;
}

void win_events(system_t *sys, win_t *win)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, win);
        if (win->str == WIN_ENTER)
            text_textbox(event, win->name);
        else
            switch_scene(event, sys, win, sys->state);
    }
}
