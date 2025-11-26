/*
** EPITECH PROJECT, 2025
** G-MUL-100-BDX-1-1-myhunter-3
** File description:
** events
*/

#include "funct.h"

static void update_car_info(car_t *c, float bgW)
{
    c->pos.x = bgW * 0.2f;
    c->pos.y = rand() % 700 + 100;
    sfSprite_setPosition(c->sprite, c->pos);
    sfSprite_setPosition(c->ball->sprite,
        (sfVector2f){c->pos.x + 90, c->pos.y - 39});
    c->boost->is_visibe = false;
    c->speed = SPEED;
    is_boost(c);
    c->sleep = 0;
    wait_time(c);
}

static void touch_car(car_t *c, game_t *game, sfVector2f mouse)
{
    const sfTexture *tex = sfSprite_getTexture(game->background);
    sfVector2u sizeTex = sfTexture_getSize(tex);
    sfVector2f scale = sfSprite_getScale(game->background);
    float bgW = sizeTex.x * scale.x;

    if (mouse.x >= bgW * 0.7f) {
        sfSound_play(game->save->sound);
        if (game->life < 3)
            game->life++;
    } else {
        sfSound_play(game->demo->sound);
    }
    game->score++;
    game->explo->pos = c->pos;
    game->explo->is_visible = true;
    game->explo->area.left = 0;
    sfSprite_setPosition(game->explo->sprite, game->explo->pos);
    
    update_car_info(c, bgW);
}

void handle_click(sfRenderWindow *window, game_t *game, car_t **car)
{
    sfVector2i pixel = sfMouse_getPositionRenderWindow(window);
    sfVector2f mouse = sfRenderWindow_mapPixelToCoords(window, pixel, NULL);
    car_t *c;

    for (int i = 0; i < NB_CAR; i++) {
        c = car[i];
        if (mouse.x >= c->pos.x - 55 && mouse.x <= c->pos.x + 110 &&
            mouse.y >= c->pos.y - 20 && mouse.y <= c->pos.y + 60)
            touch_car(c, game, mouse);
    }
}

static sfVector2f get_mouse(sfRenderWindow *window)
{
    sfVector2i pixel = sfMouse_getPositionRenderWindow(window);
    sfVector2f mouse = sfRenderWindow_mapPixelToCoords(window, pixel, NULL);

    return mouse;
}

static void start(sfVector2f mouse, game_t *game, int map)
{
    if (mouse.x >= game->btn->pos.x - 180
        && mouse.x <= game->btn->pos.x + 180
        && mouse.y >= game->btn->pos.y - 55
        && mouse.y <= game->btn->pos.y + 55) {
        game->is_play = true;
        game->background = create_sprite(concat3("assets/Map_",
            int_to_str(map), ".png"), NULL, 1.428, 1.406);
        sfMusic_play(game->music);
    }
}

static void btn_1(sfVector2f mouse, game_t *game, car_t **car)
{
    if (mouse.x >= game->btn_1->pos.x - 75
        && mouse.x <= game->btn_1->pos.x + 75
        && mouse.y >= game->btn_1->pos.y - 75
        && mouse.y <= game->btn_1->pos.y + 75) {
        game->car->nb = 1;
        change_car(game->car->nb, car, game);
    }
}

static void btn_2(sfVector2f mouse, game_t *game, car_t **car)
{
    if (mouse.x >= game->btn_2->pos.x - 75
        && mouse.x <= game->btn_2->pos.x + 75
        && mouse.y >= game->btn_2->pos.y - 75
        && mouse.y <= game->btn_2->pos.y + 75) {
        game->car->nb = 2;
        change_car(game->car->nb, car, game);
    }
}

void start_click(sfRenderWindow *window, game_t *game, car_t **car)
{
    sfVector2f mouse = get_mouse(window);
    int map = rand() % 3 + 1;

    start(mouse, game, map);
    btn_1(mouse, game, car);
    btn_2(mouse, game, car);
}

void events(sfRenderWindow *window, game_t *game, car_t **car)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtMouseButtonPressed &&
            event.mouseButton.button == sfMouseLeft &&
            game->is_play == true) {
            handle_click(window, game, car);
        }
        if (event.type == sfEvtMouseButtonPressed &&
            event.mouseButton.button == sfMouseLeft &&
            game->is_play == false)
            start_click(window, game, car);
    }
}
