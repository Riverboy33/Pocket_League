/*
** EPITECH PROJECT, 2025
** G-MUL-100-BDX-1-1-myhunter-3
** File description:
** update
*/

#include "funct.h"

void update_ball_animation(ball_t *ball)
{
    sfTime elapsed = sfClock_getElapsedTime(ball->anim_clock);
    float seconds = sfTime_asSeconds(elapsed);

    if (seconds > 0.15f) {
        ball->area.left += 126;
        if (ball->area.left >= 630)
            ball->area.left = 0;
        sfSprite_setTextureRect(ball->sprite, ball->area);
        sfClock_restart(ball->anim_clock);
    }
}

void update_boost_animation(boost_t *boost)
{
    sfTime elapsed = sfClock_getElapsedTime(boost->anim_clock);
    float seconds = sfTime_asSeconds(elapsed);

    if (seconds > 0.15f) {
        boost->area.left += 280;
        if (boost->area.left >= 1120)
            boost->area.left = 0;
        sfSprite_setTextureRect(boost->sprite, boost->area);
        sfClock_restart(boost->anim_clock);
    }
}

static void play_chat(game_t *game)
{
    game->chat->is_visible = true;
    sfSound_play(game->chat->msg->sound);
    sfClock_restart(game->chat->clock);
}

static float get_width(game_t *game)
{
    const sfTexture *tex = sfSprite_getTexture(game->background);
    sfVector2u sizeTex = sfTexture_getSize(tex);
    sfVector2f scale = sfSprite_getScale(game->background);

    return sizeTex.x * scale.x;
}

static void move_sprites(car_t *c)
{
    sfSprite_setPosition(c->sprite, c->pos);
    sfSprite_setPosition(c->ball->sprite, (sfVector2f){c->pos.x + 90,
        c->pos.y - 39});
    update_ball_animation(c->ball);
    sfSprite_setPosition(c->boost->sprite, (sfVector2f){c->pos.x - 135,
        c->pos.y - 25});
    update_boost_animation(c->boost);
}

static void set_speed_and_boost(car_t *c)
{
    c->speed = SPEED;
    c->boost->is_visibe = false;
    is_boost(c);
    c->sleep = 0;
    wait_time(c);
}

void update_cars(game_t *game, sfTime elapsed, car_t **car)
{
    float dt = sfTime_asSeconds(elapsed);
    float bgW = get_width(game);
    car_t *c = NULL;

    for (int i = 0; i < NB_CAR; i++) {
        c = car[i];
        if (c->is_visible)
            c->pos.x += car[i]->speed * dt;
        if (c->pos.x > (bgW * 0.8f) - 150) {
            c->pos.x = bgW * 0.2f;
            c->pos.y = rand() % 700 + 100;
            game->life--;
            set_speed_and_boost(c);
            play_chat(game);
        }
        move_sprites(c);
    }
}

void update_demo(game_t *game)
{
    sfTime elapsed = sfClock_getElapsedTime(game->explo->clock);
    float seconds = sfTime_asSeconds(elapsed);

    if (seconds > 0.15f && game->explo->is_visible) {
        game->explo->area.left += 360;
        if (game->explo->area.left >= 1440)
            game->explo->is_visible = false;
        sfSprite_setTextureRect(game->explo->sprite, game->explo->area);
        sfClock_restart(game->explo->clock);
    }
}

void update_highscore(game_t *game)
{
    if (game->score > game->high_score)
        game->high_score = game->score;
}

void change_car(int car_nb, car_t **car, game_t *game)
{
    car_t *c = NULL;

    for (int i = 0; i < NB_CAR; i++) {
        c = car[i];
        c->sprite = create_sprite(concat3("assets/Car_",
            int_to_str(car_nb), ".png"), NULL, 0.25, 0.25);
        check_sprite(c->sprite);
        sfSprite_setOrigin(c->sprite, (sfVector2f){86.45, 45.5});
    }
    game->car->sprite = create_sprite(concat3("assets/Car_",
        int_to_str(car_nb), ".png"), NULL, 1, 1);
    check_sprite(game->car->sprite);
    game->car->pos = (sfVector2f){750, 400};
    sfSprite_setPosition(game->car->sprite, game->car->pos);
}
