/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** element
*/

#ifndef ELEMENT_H_
    #define ELEMENT_H_

    #include "game.h"
    #include "save.h"

    #define ITEM_RANGE 15.0

typedef enum item_id_e {
    I_SMALL_HEALTH,
    I_BIG_HEALTH,
    I_AMMO_PISTOL,
    I_AMMO_SHUTGUN,
    I_AMMO_MINIGUN,
    I_STAMINA,
    I_FLASHLIGHT,
    I_WEAPON_TWO,
    I_WEAPON_THREE,
    I_WEAPON_FOUR,
    NB_ITEM,
} item_id_t;

typedef enum enemy_id_e {
    E_SWORD,
    E_GUN,
    NB_ENEMY,
} enemy_id_t;

typedef struct item_s {
    int id;
    item_id_t type;
    sfVector2f pos;
    float dist;
} item_t;

typedef struct enemy_s {
    int id;
    enemy_id_t type;
    sfVector2f pos;
    int health;
    float dist;
    float cooldown;
} enemy_t;

typedef enum {
    I_TYPE,
    I_POS_X,
    I_POS_Y,
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
    int quantity;
    item_info_t info;
} get_item_t;

static const get_item_t ITEM[] __maybe_unused = {
    [I_SMALL_HEALTH] = {&item_potion, MAX_HEALTH, MAX_HEALTH / 2, INFO_HEALTH},
    [I_BIG_HEALTH] = {&item_potion, MAX_HEALTH, MAX_HEALTH, INFO_HEALTH},
    [I_AMMO_PISTOL] = {&item_potion, MAX_AMMO, 15, INFO_AMMO_PISTOL},
    [I_AMMO_SHUTGUN] = {&item_potion, MAX_AMMO, 7, INFO_AMMO_SHUTGUN},
    [I_AMMO_MINIGUN] = {&item_potion, MAX_AMMO, 50, INFO_AMMO_MINIGUN},
    [I_STAMINA] = {&item_potion, MAX_HEALTH, MAX_HEALTH, INFO_STAMINA},
    [I_FLASHLIGHT] = {&item_potion, MAX_HEALTH, MAX_HEALTH, INFO_FLASHLIGHT},
    [I_WEAPON_TWO] = {&item_weapon},
    [I_WEAPON_THREE] = {&item_weapon},
    [I_WEAPON_FOUR] = {&item_weapon},
};

typedef struct enemy_info_s {
    int detect_range;
    int attack;
    int attack_range;
    int cooldown;
    int speed;
    char const *path;
} enemy_info_t;

static const enemy_info_t ENEMY[] __maybe_unused = {
    [E_SWORD] = {RENDER_DISTANCE, 25, 15, 3, 150, "asset/soldier.png"},
    [E_GUN] = {RENDER_DISTANCE, 10, 128, 2, 50, "asset/soldier.png"}
};

    #define NB_ENEMIES ARRAY_LENGTH(ENEMY)

void handle_items(save_t *save);

#endif /* !ELEMENT_H_ */
