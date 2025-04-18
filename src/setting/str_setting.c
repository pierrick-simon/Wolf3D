/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** setting_str
*/

#include "wolf.h"

const draw_textbox_t str_setting[] = {
    {"BOOM", (sfVector2f){WIN_WIDTH * 4 / 7, WIN_HEIGHT * 5 / 100},
        250, SETTING},
    {"Fullscreen", (sfVector2f){WIN_WIDTH * 4 / 7 + 75, WIN_HEIGHT * 7 / 20},
        75, SETTING},
    {"Sound", (sfVector2f){WIN_WIDTH * 4 / 7 + 75, WIN_HEIGHT * 12 / 20},
        75, SETTING},
    {"Back", (sfVector2f){WIN_WIDTH * 4 / 7 + 75, WIN_HEIGHT * 17 / 20},
        75, MENU},
};
