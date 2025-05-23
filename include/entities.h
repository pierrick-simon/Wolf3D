/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** element
*/

#ifndef ELEMENT_H_
    #define ELEMENT_H_

    #include "save.h"

    #define ITEM_RANGE 30.0
    #define DEATH_RECT 0.075

    #define NB_ITEM E_SWORD_ENEMY

    #define HEAD 1.5

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
    E_CYBORG,
    E_GROWLER,
    E_PHANTOM,
    E_BOSS,
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
    sfVector2f next_pos;
    sfVector2i prev_tile;
    sfVector2f offset;
    sfBool is_alive;
    float dist;
    int health;
    float cooldown;
    float change_rect;
    float damage;
    float change_pos;
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
    float factor;
    float y;
    int max_first;
    int max_second;
    int max_third;
    sfVector2f hit_start;
    sfVector2f hit_end;
    sfVector2f weak_start;
    sfVector2f weak_end;
} entity_info_t;

    #define DIST_OFFSET 5000

static const entity_info_t ENTITY[] __maybe_unused = {
    [E_SMALL_HEALTH] = {"asset/health1.png",
        {14, 15}, 0.15, 6, 3},
    [E_BIG_HEALTH] = {"asset/health2.png",
        {28, 19}, 0.3, 6, 3},
    [E_STAMINA] = {"asset/potion.png",
        {14, 18}, 0.2, 6},
    [E_AMMO_PISTOL] = {"asset/pistol_ammo.png",
        {9, 11}, 0.15, 6},
    [E_AMMO_SHUTGUN] = {"asset/shotgun_ammo.png",
        {32, 12}, 0.3, 6},
    [E_AMMO_MINIGUN] = {"asset/minigun_ammo.png",
        {28, 16}, 0.3, 6},
    [E_FLASHLIGHT] = {"asset/batterie.png",
        {7, 11}, 0.1, 6},
    [E_WEAPON_TWO] = {"asset/floor_gun.png",
        {29, 14}, 0.2, 6},
    [E_WEAPON_THREE] = {"asset/floor_shotgun.png",
        {63, 12}, 0.5, 6},
    [E_WEAPON_FOUR] = {"asset/floor_minigun.png",
        {54, 16}, 0.4, 6},
    [E_SWORD_ENEMY] = {"asset/sword.png",
        {79, 83}, 1, 1, 4, 3, 9,
        {0.15, 0.15}, {0.85, 1}, {0.15, 0.15}, {0.85, 0.4}},
    [E_GUN_ENEMY] = {"asset/soldier.png",
        {42, 55}, 0.8, 1, 4, 2, 8,
        {0, 0}, {0.85, 1}, {0, 0}, {0.85, 0.3}},
    [E_SHEET_ENEMY] = {"asset/sheet.png",
        {640, 670}, 0.8, 1, 1, 0, 0,
        {0, 0}, {1, 1}, {0, 0}, {0, 0}},
    [E_CYBORG] = {"asset/cyborg.png",
        {67, 59}, 0.8, 1, 4, 2, 5,
        {0.15, 0}, {0.85, 1}, {0.15, 0}, {0.85, 0.3}},
    [E_GROWLER] = {"asset/growler.png",
        {80, 91}, 0.8, 1, 3, 2, 6,
        {0.15, 0}, {0.70, 1}, {0.15, 0}, {0.70, 0.3}},
    [E_PHANTOM] = {"asset/phantom.png",
        {65, 60}, 0.8, 1, 3, 3, 6,
        {0.15, 0}, {0.85, 1}, {0.15, 0.4}, {0.85, 0.6}},
    [E_BOSS] = {"asset/boss.png",
        {161, 85}, 1.8, 1, 5, 2, 11,
        {0.2, 0}, {0.8, 0.7}, {0.3, 0}, {0.7, 0.5}},
};

typedef struct enemy_info_s {
    float attack;
    float attack_range;
    float cooldown;
    float speed;
    float score;
    float health;
} enemy_info_t;

static const enemy_info_t ENEMY[] __maybe_unused = {
    [E_SWORD_ENEMY] = {8, 32, 1, 100, 100, 150},
    [E_GUN_ENEMY] = {7, 300, 2, 50, 175, 100},
    [E_SHEET_ENEMY] = {1, 15, 3, 150, 1, 1},
    [E_CYBORG] = {17, 450, 5, 30, 250, 100},
    [E_GROWLER] = {2, 250, 0.5, 50, 25, 25},
    [E_PHANTOM] = {17, 32, 4, 30, 250, 250},
    [E_BOSS] = {15, 350, 4, 10, 10000, 1000},
};

typedef struct closer_tile_s {
    sfVector2i *next;
    sfVector2i *cmp;
    sfVector2i prev;
    float *dist;
} closer_tile_t;

typedef struct draw_entity_s {
    sfVector2f diff;
    float inv;
    sfVector2f dist;
    int x;
    int size;
    sfVector2i start;
    sfVector2i end;
    entity_t *entity;
} draw_entity_t;

void handle_items(save_t *save, game_t *game);

#endif /* !ELEMENT_H_ */
