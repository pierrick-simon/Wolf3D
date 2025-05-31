/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "editor.h"
#include "save.h"
#include <string.h>

static void nb_textbox(sfEvent event, char *str)
{
    int len = strlen(str);

    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeyBackspace && len > 0)
            str[len - 1] = '\0';
        if (event.key.code >= sfKeyNum0 && event.key.code <= sfKeyNum9
            && len < MAX_STRLEN)
            str[len] = event.key.code + '0' - sfKeyNum0;
        if (event.key.code == 51 && len < MAX_STRLEN)
            str[len] = '4';
        if (event.key.code == 56 && len < MAX_STRLEN)
            str[len] = '6';
    }
}

static void text_textbox(sfEvent event, char *str)
{
    int len = strlen(str);

    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeyBackspace && len > 0)
            str[len - 1] = '\0';
        if (event.key.code >= sfKeyA && event.key.code <= sfKeyZ
            && len < MAX_NAME) {
            str[len] = event.key.code + 'a' - sfKeyA;
            str[len + 1] = '\0';
        }
    }
}

static void switch_scene(sfEvent event,
    edit_info_t *edit_info, state_info_t *state)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0)
        || is_input(event, sfKeyEscape, sfTrue, 7)) {
        if (is_input(event, sfKeyEscape, sfTrue, 7))
            edit_info->str = EDIT_INF_BACK;
        state->old_scene = state->scene;
        state->scene = edit_info->draw[edit_info->str].scene;
        edit_info->draw[edit_info->str].color = sfWhite;
        edit_info->str = EDIT_INF_NAME;
    }
}

static void switch_str(sfEvent event, edit_info_t *edit_info)
{
    edit_info->draw[edit_info->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK)
        edit_info->str--;
    if (is_input(event, sfKeyDown, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK)
        edit_info->str++;
    if (edit_info->str == NB_EDIT_INF)
        edit_info->str = EDIT_INF_NAME;
    if (edit_info->str == EDIT_INF_TITLE)
        edit_info->str = EDIT_INF_BACK;
    edit_info->draw[edit_info->str].color = sfRed;
}

void edit_info_events(system_t *sys, edit_info_t *edit_info)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, edit_info);
        switch_scene(event, edit_info, sys->state);
        if (edit_info->str == EDIT_INF_NAME)
            text_textbox(event, edit_info->string[edit_info->str]);
        if (edit_info->str == EDIT_INF_X || edit_info->str == EDIT_INF_Y)
            nb_textbox(event, edit_info->string[edit_info->str]);
    }
}
