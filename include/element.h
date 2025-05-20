/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** element
*/

#ifndef ELEMENT_H_
    #define ELEMENT_H_

    #include "game.h"

    #define ITEM_RANGE 15.0

typedef enum item_id_e {
    I_HEALTH,
    I_AMMO,
    I_STAMINA,
    I_FLASHLIGHT,
    I_WEAPON_TWO,
    I_WEAPON_THREE,
    I_WEAPON_FOUR,
    NB_ITEM,
} item_id_t;

typedef enum enemy_id_e {
    E_NORMAL,
    NB_ENEMY,
} enemy_id_t;

typedef struct item_s {
    int id;
    item_id_t type;
    sfVector2f pos;
    int quantity;
    int dist;
} item_t;

typedef struct enemy_s {
    int id;
    enemy_id_t type;
    sfVector2f pos;
    int health;
    int dist;
    float cooldown;
} enemy_t;


typedef enum {
    I_TYPE,
    I_POS_X,
    I_POS_Y,
    I_QUANTITY,
    NB_STR_ITEM,
} str_item_t;

typedef enum {
    E_TYPE,
    E_POS_X,
    E_POS_Y,
    E_HEALTH,
    NB_STR_ENEMY,
} str_enemy_t;

void item_weapon(int quantity, int *item, int max);
void item_potion(int quantity, int *item, int max);

typedef struct get_item_s {
    void (*func)(int quantity, int *item, int max);
    int max;
} get_item_t;

static const get_item_t ITEM[] __maybe_unused = {
    [I_HEALTH] = {&item_potion, MAX_HEALTH},
    [I_AMMO] = {&item_potion, MAX_AMMO},
    [I_STAMINA] = {&item_potion, MAX_HEALTH},
    [I_FLASHLIGHT] = {&item_potion, MAX_HEALTH},
    [I_WEAPON_TWO] = {&item_weapon, 15},
    [I_WEAPON_THREE] = {&item_weapon, 15},
    [I_WEAPON_FOUR] = {&item_weapon, 15},
};

typedef struct enemy_info_s {
    int detect_range;
    int attack;
    int attack_range;
    int cooldown;
    int speed;
} enemy_info_t;

static const enemy_info_t ENEMY[] __maybe_unused = {
    [0] = {RENDER_DISTANCE, 10, 50, 3, 100}
};

void handle_items(save_t *save);

#endif /* !ELEMENT_H_ */
