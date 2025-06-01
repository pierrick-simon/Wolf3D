/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "editor.h"
#include "save.h"
#include <string.h>
#include <stdlib.h>

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

static void fill_map(save_t *save, int i)
{
    for (int j = 0; j < save->size.x; j++) {
        if (i == 0 || i == save->size.y - 1
            || j == 0 || j == save->size.y - 1)
            save->map[i][j] = 1;
        else
            save->map[i][j] = 0;
    }
}

static void init_save_info(save_t *save)
{
    save->music_path = "asset/music.ogg";
    save->info->difficulty = 1;
    save->info->start_weapon = 1;
    save->info->weapons = 1;
    save->info->time = 0;
    save->info->score = 0;
    save->info->start_angle = 0;
    save->info->item_info[INFO_HEALTH] = MAX_HEALTH;
    save->info->item_info[INFO_STAMINA] = MAX_HEALTH;
    save->info->item_info[INFO_FLASHLIGHT] = MAX_HEALTH;
    save->info->item_info[INFO_AMMO_PISTOL] = 15;
    save->info->item_info[INFO_AMMO_SHUTGUN] = 7;
    save->info->item_info[INFO_AMMO_MINIGUN] = 50;
    save->info->start_pos = (sfVector2f){70, 70};
}

static void update_save(system_t *sys, edit_info_t *edit_info)
{
    if (edit_info->str != EDIT_INF_Y)
        return;
    destroy_save(sys->save);
    sys->save->name = strdup(edit_info->string[EDIT_INF_NAME]);
    sys->save->size.x = atoi(edit_info->string[EDIT_INF_X]) + 1;
    sys->save->size.y = atoi(edit_info->string[EDIT_INF_Y]) + 1;
    sys->save->map = malloc(sizeof(int *) * sys->save->size.y);
    for (int i = 0; i < sys->save->size.y; i++) {
        sys->save->map[i] = malloc(sizeof(int) * sys->save->size.x);
        fill_map(sys->save, i);
    }
    init_save_info(sys->save);
}

static void switch_scene(sfEvent event, system_t *sys,
    edit_info_t *edit_info, state_info_t *state)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0)
        || is_input(event, sfKeyEscape, sfTrue, 7)) {
        if (is_input(event, sfKeyEscape, sfTrue, 7))
            edit_info->str = EDIT_INF_BACK;
        if (edit_info->str == EDIT_INF_NAME || edit_info->str == EDIT_INF_X) {
            edit_info->draw[edit_info->str].color = sfWhite;
            edit_info->str++;
            return;
        }
        update_save(sys, edit_info);
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
        switch_scene(event, sys, edit_info, sys->state);
        if (edit_info->str == EDIT_INF_NAME)
            text_textbox(event, edit_info->string[edit_info->str]);
        if (edit_info->str == EDIT_INF_X || edit_info->str == EDIT_INF_Y)
            nb_textbox(event, edit_info->string[edit_info->str]);
    }
}
