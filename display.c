/*
** EPITECH PROJECT, 2025
** G-MUL-100-BDX-1-1-myhunter-3
** File description:
** display
*/

#include "funct.h"

static void create_crosshair(sfVector2i mouse, sfRenderWindow *window,
    sfVector2f pos, game_t *game)
{
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    mouse = sfMouse_getPositionRenderWindow(window);
    pos = sfRenderWindow_mapPixelToCoords(window, mouse, NULL);
    sfSprite_setPosition(game->crosshair->sprite, pos);
}

static void create_text(game_t *game)
{
    char *score_str = int_to_str(game->score);
    char *life_str = int_to_str(3 - game->life);
    char *full = concat3(life_str, " | ", score_str);

    sfText_setString(game->text, full);
    free(score_str);
    free(life_str);
    free(full);
}

static void loop_on_car(car_t *c, sfRenderWindow *window)
{
    sfTime elapsed_wait;
    float seconds_wait;

    elapsed_wait = sfClock_getElapsedTime(c->sleep_clock);
        seconds_wait = sfTime_asSeconds(elapsed_wait);
        if (seconds_wait >= c->sleep) {
            c->is_visible = true;
            sfRenderWindow_drawSprite(window, c->sprite, NULL);
            sfRenderWindow_drawSprite(window, c->ball->sprite, NULL);
            if (c->boost->is_visibe)
                sfRenderWindow_drawSprite(window, c->boost->sprite, NULL);
        }
}

void display(sfRenderWindow *window, game_t *game, car_t **car)
{
    sfVector2i mouse;
    sfVector2f pos;
    sfColor color = sfColor_fromRGB(0, 0, 0);
    car_t *c;

    sfRenderWindow_clear(window, color);
    create_crosshair(mouse, window, pos, game);
    sfRenderWindow_drawSprite(window, game->background, NULL);
    create_text(game);
    for (int i = 0; i < NB_CAR; i++) {
        c = car[i];
        loop_on_car(c, window);
    }
    game->chat->dt = sfTime_asSeconds(
        sfClock_getElapsedTime(game->chat->clock));
    if (game->chat->is_visible && game->chat->dt < 3)
        sfRenderWindow_drawText(window, game->chat->text, NULL);
    game->explo->dt = sfTime_asSeconds(
        sfClock_getElapsedTime(game->explo->clock));
    if (game->explo->is_visible)
        sfRenderWindow_drawSprite(window, game->explo->sprite, NULL);
    sfRenderWindow_drawText(window, game->text, NULL);
    sfRenderWindow_drawSprite(window, game->crosshair->sprite, NULL);
    sfRenderWindow_display(window);
}

void display_start(sfRenderWindow *window, game_t *game)
{
    char *high_score = int_to_str(game->high_score);
    char *full = concat3("High score : ", high_score, "");
    sfColor color = sfColor_fromRGB(0, 0, 0);

    sfRenderWindow_clear(window, color);
    sfRenderWindow_setMouseCursorVisible(window, sfTrue);
    sfRenderWindow_drawSprite(window, game->start, NULL);
    sfRenderWindow_drawSprite(window, game->btn->sprite, NULL);
    sfRenderWindow_drawSprite(window, game->btn_1->sprite, NULL);
    sfRenderWindow_drawSprite(window, game->btn_2->sprite, NULL);
    sfText_setString(game->text_start, full);
    free(high_score);
    free(full);
    sfRenderWindow_drawText(window, game->text_start, NULL);
    sfRenderWindow_drawSprite(window, game->logo, NULL);
    sfRenderWindow_drawSprite(window, game->car->sprite, NULL);
    sfRenderWindow_display(window);
}
