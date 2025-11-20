/*
** EPITECH PROJECT, 2025
** G-PSU-100-BDX-1-1-myls-3
** File description:
** my_ls
*/

#include <stdbool.h>

#ifndef MY_LS_H
    #define MY_LS_H
    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0
    #define SPEED 350.0
    #define NB_CAR 5

typedef struct btn_s {
    sfSprite *sprite;
    sfVector2f pos;
} btn_t;

typedef struct crosshair_s{
    sfSprite *sprite;
    sfVector2f pos;
} crosshair_t;

typedef struct car_sprite_s{
    int nb;
    sfSprite *sprite;
    sfVector2f pos;
} car_sprite_t;

typedef struct sound_s{
    sfSound *sound;
    sfSoundBuffer *buff;
} sound_t;

typedef struct chat_s {
    sfText *text;
    sfVector2f pos;
    sfFont *font;
    bool is_visible;
    sound_t *msg;
    sfClock *clock;
    float dt;
} chat_t;

typedef struct game_s {
    sfSprite *background;
    sfSprite *start;
    btn_t *btn;
    int score;
    int life;
    bool is_play;
    sfText *text;
    sfText *text_start;
    sfFont *font;
    int high_score;
    sfSprite *logo;
    crosshair_t *crosshair;
    btn_t *btn_1;
    btn_t *btn_2;
    car_sprite_t *car;
    sfMusic *music;
    sound_t *demo;
    sound_t *save;
    chat_t *chat;
} game_t;

typedef struct ball_s {
    sfSprite *sprite;
    sfVector2f pos;
    sfIntRect area;
    sfClock *anim_clock;
} ball_t;

typedef struct boost_s{
    sfSprite *sprite;
    sfVector2f pos;
    sfIntRect area;
    sfClock *anim_clock;
    bool is_visibe;
} boost_t;

typedef struct car_s {
    sfSprite *sprite;
    sfVector2f pos;
    ball_t *ball;
    boost_t *boost;
    double speed;
    float sleep;
    sfClock *sleep_clock;
    bool is_visible;
} car_t;

#endif /*MY_LS_H*/
