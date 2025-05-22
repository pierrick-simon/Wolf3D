/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** element
*/

#ifndef ELEMENT_H_
    #define ELEMENT_H_

    #include "save.h"

    #define ITEM_RANGE 15.0

    #define NB_ITEM E_SWORD_ENEMY

typedef struct game_s game_t;

typedef enum entity_id_e {
    E_SMALL_HEALTH,
    E_BIG_HEALTH,
    E_STAMINA,
    E_AMMO_PISTOL,
    E_AMMO_SHUTGUN,
    E_AMMO_MINIGUN,
    E_FLASHLIGHT,
    E_WEAPON_TWO,
    E_WEAPON_THREE,
    E_WEAPON_FOUR,
    E_SWORD_ENEMY,
    E_GUN_ENEMY,
    E_SHEET_ENEMY,
    NB_ENTITIES,
} entity_id_t;

typedef enum {
    E_TYPE,
    E_POS_X,
    E_POS_Y,
    E_INFO,
    NB_STR_ENTITIES,
} str_entity_t;

typedef struct entity_s {
    entity_id_t type;
    sfVector2f pos;
    float dist;
    int health;
    float cooldown;
    int id;
} entity_t;


void item_weapon(int quantity, int *item, int max);
void item_potion(int quantity, int *item, int max);

typedef struct get_item_s {
    void (*func)(int quantity, int *item, int max);
    int max;
    int quantity;
    item_info_t info;
} get_item_t;

static const get_item_t ITEM[] __maybe_unused = {
    [E_SMALL_HEALTH] = {&item_potion, MAX_HEALTH, MAX_HEALTH / 2, INFO_HEALTH},
    [E_BIG_HEALTH] = {&item_potion, MAX_HEALTH, MAX_HEALTH, INFO_HEALTH},
    [E_AMMO_PISTOL] = {&item_potion, MAX_AMMO, 15, INFO_AMMO_PISTOL},
    [E_AMMO_SHUTGUN] = {&item_potion, MAX_AMMO, 7, INFO_AMMO_SHUTGUN},
    [E_AMMO_MINIGUN] = {&item_potion, MAX_AMMO, 50, INFO_AMMO_MINIGUN},
    [E_STAMINA] = {&item_potion, MAX_HEALTH, MAX_HEALTH, INFO_STAMINA},
    [E_FLASHLIGHT] = {&item_potion, MAX_HEALTH, MAX_HEALTH, INFO_FLASHLIGHT},
    [E_WEAPON_TWO] = {&item_weapon},
    [E_WEAPON_THREE] = {&item_weapon},
    [E_WEAPON_FOUR] = {&item_weapon},
};

typedef struct entity_info_s {
    char const *path;
    sfVector2f text_size;
} entity_info_t;

static const entity_info_t ENTITY[] __maybe_unused = {
    [E_SMALL_HEALTH] = {"asset/health1.png", {14, 15}},
    [E_BIG_HEALTH] = {"asset/health2.png", {28, 19}},
    [E_STAMINA] = {"asset/potion.png", {14, 18}},
    [E_AMMO_PISTOL] = {"asset/pistol_ammo.png", {9, 11}},
    [E_AMMO_SHUTGUN] = {"asset/shotgun_ammo.png", {32, 12}},
    [E_AMMO_MINIGUN] = {"asset/minigun_ammo.png", {28, 16}},
    [E_FLASHLIGHT] = {"asset/batterie.png", {7, 11}},
    [E_WEAPON_TWO] = {"asset/floor_gun.png", {29, 14}},
    [E_WEAPON_THREE] = {"asset/floor_shotgun.png", {63, 12}},
    [E_WEAPON_FOUR] = {"asset/floor_minigun.png", {54, 16}},
    [E_SWORD_ENEMY] = {"asset/sword.png", {48, 67}},
    [E_GUN_ENEMY] = {"asset/soldier.png", {42, 55}},
    [E_SHEET_ENEMY] = {"asset/sheet.png", {640, 670}},
};

typedef struct enemy_info_s {
    int attack;
    int attack_range;
    int cooldown;
    int speed;
} enemy_info_t;

static const enemy_info_t ENEMY[] __maybe_unused = {
    [E_SWORD_ENEMY] = {25, 15, 3, 150},
    [E_GUN_ENEMY] = {10, 128, 2, 50},
    [E_SHEET_ENEMY] = {1, 15, 3, 150}
};

typedef struct draw_entity_s {
    sfVector2f diff;
    float inv;
    sfVector2f dist;
    int x;
    int size;
    sfVector2i start;
    sfVector2i end;
    entity_t *enemy;
} draw_entity_t;

void handle_items(save_t *save, game_t *game);

#endif /* !ELEMENT_H_ */
