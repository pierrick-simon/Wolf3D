/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** draw_button
*/

#include <stdio.h>
#include "editor.h"
#include "linked_list.h"

static sfVector2f calculate_middle(sfFloatRect rect, sfFloatRect text,
    sfVector2f pos)
{
    sfVector2f position = {0};

    position.y = pos.y + (rect.height / 2 - text.height) + 3;
    position.x = pos.x + (rect.width - text.width) / 2 - 5;
    return position;
}

static void draw_button_text(system_t *sys, buttons_t *buttons, int button)
{
    sfFloatRect size_text = {0};

    sfText_setColor(sys->textbox->text, sfBlack);
    sfText_setString(sys->textbox->text, BUTTON[button].text);
    sfText_setCharacterSize(sys->textbox->text, SIZE_TEXT_BUTTON);
    size_text = sfText_getGlobalBounds(sys->textbox->text);
    sfText_setPosition(sys->textbox->text,
        calculate_middle(buttons->bounds[button], size_text,
        BUTTON[button].pos));
    sfRenderWindow_drawText(sys->window, sys->textbox->text, NULL);
    sfText_setPosition(sys->textbox->text, (sfVector2f){0, 0});
}

static void set_button_color(buttons_t *buttons, edit_map_t *edit, edit_t i)
{
    if (edit->current == NULL || edit->current->next == NULL)
        edit->color[EDIT_PREV] = sfWhite;
    else
        edit->color[EDIT_PREV] = sfMagenta;
    if (edit->current == NULL || edit->current->prev == NULL)
        edit->color[EDIT_NEXT] = sfWhite;
    else
        edit->color[EDIT_NEXT] = sfMagenta;
    sfRectangleShape_setOutlineColor(buttons->rectangle, sfBlack);
    sfRectangleShape_setOutlineThickness(buttons->rectangle, 2);
    if (buttons->hover[i] == sfTrue)
        sfRectangleShape_setOutlineThickness(buttons->rectangle, 10);
    if (buttons->hover[i] == sfFalse && edit->edit == i
        && buttons->press == sfTrue) {
        sfRectangleShape_setOutlineColor(buttons->rectangle, sfYellow);
        sfRectangleShape_setOutlineThickness(buttons->rectangle, 10);
    }
}

void draw_button(system_t *sys, buttons_t *buttons, edit_map_t *edit)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(sys->window);

    for (edit_t i = 0; i < NB_EDIT; i++) {
        edit->buttons->hover[i] = sfFloatRect_contains(
            &edit->buttons->bounds[i], mouse_pos.x, mouse_pos.y);
        sfRectangleShape_setPosition(buttons->rectangle, BUTTON[i].pos);
        sfRectangleShape_setFillColor(buttons->rectangle, edit->color[i]);
        set_button_color(buttons, edit, i);
        sfRenderWindow_drawRectangleShape(
            sys->window, buttons->rectangle, NULL);
        draw_button_text(sys, buttons, i);
    }
}
