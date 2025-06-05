/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** handle_boss
*/

#include "game.h"
#include "entities.h"
#include "linked_list.h"

void add_node_boss(linked_list_t *boss, int health)
{
    int *boss_health = malloc(sizeof(int));

    if (boss_health == NULL)
        return;
    *boss_health = health;
    push_to_tail(boss, boss_health);
}

static void draw_rectangle(system_t *sys, sfRectangleShape *rectangle,
    draw_textbox_t *draw, node_t *head)
{
    sfRectangleShape_setOutlineColor(rectangle, sfWhite);
    sfRectangleShape_setPosition(rectangle, draw->pos);
    sfRectangleShape_setSize(rectangle, (sfVector2f){800, 20});
    sfRectangleShape_setFillColor(rectangle, GREY);
    sfRenderWindow_drawRectangleShape(sys->window, rectangle, NULL);
    sfRectangleShape_setSize(rectangle, (sfVector2f){800 * *(int *)(head->data)
        / (ENEMY[E_BOSS].health * sys->save->info->difficulty), 20});
    sfRectangleShape_setFillColor(rectangle, sfMagenta);
    sfRenderWindow_drawRectangleShape(sys->window, rectangle, NULL);
}

void draw_boss_health(system_t *sys, linked_list_t *boss,
    sfRectangleShape *rectangle, draw_textbox_t *draw)
{
    draw_textbox_t tmp = draw[TOOL_BOSS];
    int i = 0;

    tmp.color = sfBlack;
    for (node_t *head = boss->head; head != NULL; head = head->next) {
        tmp.pos.x = draw[TOOL_BOSS].pos.x;
        tmp.pos.y = draw[TOOL_BOSS].pos.y + i * 100;
        draw_string(sys, sys->textbox, &tmp);
        tmp.pos.x = 560;
        tmp.pos.y = draw[TOOL_BOSS].pos.y * 4 + i * 100;
        if (*(int *)head->data < 0)
            *(int *)head->data = 0;
        draw_rectangle(sys, rectangle, &tmp, head);
        i++;
        if (i == 3)
            break;
    }
}
