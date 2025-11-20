/*
** EPITECH PROJECT, 2025
** G-MUL-100-BDX-1-1-myhunter-3
** File description:
** my_hunter
*/


// RECORD Gregoire: 358
// Adan: 196 avec revie: 543
// Alexandre: 92

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/System/Clock.h>
#include <SFML/Window/Mouse.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "include/include.h"
#include <stdlib.h>
#include <string.h>

static char *concat3(const char *s1, const char *s2, const char *s3)
{
    if (!s1 || !s2 || !s3)
        return NULL;
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    size_t len3 = strlen(s3);
    char *res = malloc(len1 + len2 + len3 + 1);
    if (!res)
        return NULL;
    size_t i = 0;
    for (size_t j = 0; j < len1; j++)
        res[i++] = s1[j];
    for (size_t j = 0; j < len2; j++)
        res[i++] = s2[j];
    for (size_t j = 0; j < len3; j++)
        res[i++] = s3[j];
    res[i] = '\0';
    return res;
}

static char *int_to_str(unsigned const int nb)
{
    unsigned int n = nb;
    int len = 1;

    while (n >= 10) {
        n /= 10;
        len++;
    }
    char *str = malloc(len + 1);
    if (!str)
        return NULL;
    str[len] = '\0';
    n = nb;
    for (int i = len - 1; i >= 0; i--) {
        str[i] = (n % 10) + '0';
        n /= 10;
    }
    return str;
}

static sfSprite *create_sprite(char *filepath, sfIntRect *area, float sx, float sy)
{
    sfTexture *texture = sfTexture_createFromFile(filepath, NULL);
    if (!texture)
        return NULL;

    sfSprite *sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);
    if (area)
        sfSprite_setTextureRect(sprite, *area);
    sfSprite_setScale(sprite, (sfVector2f){sx, sy});
    return sprite;
}

static void is_boost(car_t *c, int i)
{
    int boost = rand() % 6 + 1;

    if (boost == 1) {
        c->boost->is_visibe = true;
        c->speed = 700.0;
    }
}

static void wait_time(car_t *c)
{
    int nb = rand() % 3 + 1;

    if (nb == 1) {
        c->sleep = rand() % 2 + 0.5;
        sfClock_restart(c->sleep_clock);
        c->is_visible = false;
    }
}

static void handle_click(sfRenderWindow *window, game_t *game, car_t **car)
{
    sfVector2i pixel = sfMouse_getPositionRenderWindow(window);
    sfVector2f mouse = sfRenderWindow_mapPixelToCoords(window, pixel, NULL);

    const sfTexture *tex = sfSprite_getTexture(game->background);
    sfVector2u sizeTex = sfTexture_getSize(tex);
    sfVector2f scale = sfSprite_getScale(game->background);
    float bgW = sizeTex.x * scale.x;

    for (int i = 0; i < NB_CAR; i++) {
        car_t *c = car[i];

        if (mouse.x >= c->pos.x - 55 && mouse.x <= c->pos.x + 110 &&
            mouse.y >= c->pos.y - 20 && mouse.y <= c->pos.y + 60) {
            if (mouse.x >= bgW * 0.7f) {
                sfSound_play(game->save->sound);
                if (game->life < 3)
                    game->life++;
            } else {
                sfSound_play(game->demo->sound);
            }

            c->pos.x = bgW * 0.2f;
            c->pos.y = rand() % 700 + 100;

            sfSprite_setPosition(c->sprite, c->pos);
            sfSprite_setPosition(c->ball->sprite, (sfVector2f){c->pos.x + 90, c->pos.y - 39});
            game->score++;
            c->boost->is_visibe = false;
            c->speed = SPEED;
            is_boost(c, i);
            c->sleep = 0;
            wait_time(c);
        }
    }
}

static void change_car(int car_nb, car_t **car, game_t *game)
{
    for (int i = 0; i < NB_CAR; i++) {
        car_t *c = car[i];

        c->sprite = create_sprite(concat3("assets/Car_", int_to_str(car_nb), ".png"), NULL, 0.25, 0.25);
        sfSprite_setOrigin(c->sprite, (sfVector2f){86.45, 45.5});
    }
    game->car->sprite = create_sprite(concat3("assets/Car_", int_to_str(car_nb), ".png"), NULL, 1, 1);
    game->car->pos = (sfVector2f){750, 400};
    sfSprite_setPosition(game->car->sprite, game->car->pos);
}

static void start_click(sfRenderWindow *window, game_t *game, car_t **car)
{
    sfVector2i pixel = sfMouse_getPositionRenderWindow(window);
    sfVector2f mouse = sfRenderWindow_mapPixelToCoords(window, pixel, NULL);
    int map = rand () % 3 + 1;

    if (mouse.x >= game->btn->pos.x - 180 && mouse.x <= game->btn->pos.x + 180 &&
        mouse.y >= game->btn->pos.y - 55 && mouse.y <= game->btn->pos.y + 55) {
        game->is_play = true;
    
        game->background = create_sprite(concat3("assets/Map_", int_to_str(map), ".png"), NULL, 1.428, 1.406);
        sfMusic_play(game->music);
    }

    if (mouse.x >= game->btn_1->pos.x - 75 && mouse.x <= game->btn_1->pos.x + 75 &&
        mouse.y >= game->btn_1->pos.y - 75 && mouse.y <= game->btn_1->pos.y + 75) {
        game->car->nb = 1;
        change_car(game->car->nb, car, game);
    }

    if (mouse.x >= game->btn_2->pos.x - 75 && mouse.x <= game->btn_2->pos.x + 75 &&
        mouse.y >= game->btn_2->pos.y - 75 && mouse.y <= game->btn_2->pos.y + 75) {
        game->car->nb = 2;
        change_car(game->car->nb, car, game);
    }
}

static void update_ball_animation(ball_t *ball)
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

static void update_boost_animation(boost_t *boost)
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

static void update_cars(game_t *game, sfTime elapsed, car_t **car)
{
    float dt = sfTime_asSeconds(elapsed);

    const sfTexture *tex = sfSprite_getTexture(game->background);
    sfVector2u sizeTex = sfTexture_getSize(tex);
    sfVector2f scale = sfSprite_getScale(game->background);
    float bgW = sizeTex.x * scale.x;

    for (int i = 0; i < NB_CAR; i++) {
        car_t *c = car[i];

        if (c->is_visible)
            c->pos.x += car[i]->speed * dt;
        if (c->pos.x > (bgW * 0.8f) - 150) {
            c->pos.x = bgW * 0.2f;
            c->pos.y = rand() % 700 + 100;
            game->life--;
            c->boost->is_visibe = false;
            c->speed = SPEED;
            is_boost(c, i);
            c->sleep = 0;
            wait_time(c);
            game->chat->is_visible = true;
            sfSound_play(game->chat->msg->sound);
            sfClock_restart(game->chat->clock);
        }
        sfSprite_setPosition(c->sprite, c->pos);
        sfSprite_setPosition(c->ball->sprite, (sfVector2f){c->pos.x + 90, c->pos.y - 39});
        update_ball_animation(c->ball);
        sfSprite_setPosition(c->boost->sprite, (sfVector2f){c->pos.x - 135, c->pos.y - 25});
        update_boost_animation(car[i]->boost);
    }
}

static void update_highscore(game_t *game)
{
    if (game->score > game->high_score)
        game->high_score = game->score;
}

static void display(sfRenderWindow *window, game_t *game, car_t **car)
{
    sfTime elapsed_wait;
    float seconds_wait;
    char *score_str = int_to_str(game->score);
    char *life_str = int_to_str(3 - game->life);
    char *full = concat3(life_str, " | ", score_str);
    sfVector2i mouse;
    sfVector2f pos;
    sfColor color = sfColor_fromRGB(0, 0, 0);

    sfRenderWindow_clear(window, color);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    mouse = sfMouse_getPositionRenderWindow(window);
    pos = sfRenderWindow_mapPixelToCoords(window, mouse, NULL);
    sfSprite_setPosition(game->crosshair->sprite, pos);
    sfRenderWindow_drawSprite(window, game->background, NULL);

    sfText_setString(game->text, full);
    free(score_str);
    free(life_str);
    free(full);

    for (int i = 0; i < NB_CAR; i++) {
        elapsed_wait = sfClock_getElapsedTime(car[i]->sleep_clock);
        seconds_wait = sfTime_asSeconds(elapsed_wait);
        if (seconds_wait >= car[i]->sleep) {
            car[i]->is_visible = true;
            sfRenderWindow_drawSprite(window, car[i]->sprite, NULL);
            sfRenderWindow_drawSprite(window, car[i]->ball->sprite, NULL);
            if (car[i]->boost->is_visibe)
                sfRenderWindow_drawSprite(window, car[i]->boost->sprite, NULL);
        }
    }
    game->chat->dt = sfTime_asSeconds(sfClock_getElapsedTime(game->chat->clock));
    if (game->chat->is_visible && game->chat->dt < 3)
        sfRenderWindow_drawText(window, game->chat->text, NULL);
    sfRenderWindow_drawText(window, game->text, NULL);
    sfRenderWindow_drawSprite(window, game->crosshair->sprite, NULL);
    sfRenderWindow_display(window);
}

static void display_start(sfRenderWindow *window, game_t *game)
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

static void init_game(game_t *game)
{
    int map = rand () % 3 + 1;

    game->text = sfText_create();
    game->font = sfFont_createFromFile("assets/font.ttf");
    sfText_setFont(game->text, game->font);
    sfText_setPosition(game->text, (sfVector2f){885, 20});
    sfText_setCharacterSize(game->text, 80);

    game->text_start = sfText_create();
    sfText_setFont(game->text_start, game->font);
    sfText_setPosition(game->text_start, (sfVector2f){1600, 500});
    sfText_setCharacterSize(game->text_start, 40);

    game->chat->font = sfFont_createFromFile("assets/chat.ttf");
    game->chat->text = sfText_create();
    sfText_setFont(game->chat->text, game->chat->font);
    sfText_setPosition(game->chat->text, (sfVector2f){20, 20});
    sfText_setCharacterSize(game->chat->text, 40);
    sfText_setString(game->chat->text, "BOT: What a save!");

    game->life = 3;
    game->background = create_sprite(concat3("assets/Map_", int_to_str(map), ".png"), NULL, 1.428, 1.406);
    game->start = create_sprite("assets/start_screen.png", NULL, 1.428, 1.406);

    game->btn->sprite = create_sprite("assets/start_btn.png", NULL, 1, 1);
    sfSprite_setOrigin(game->btn->sprite, (sfVector2f){240, 135});
    game->btn->pos = (sfVector2f){250, 650};
    sfSprite_setPosition(game->btn->sprite, game->btn->pos);
    game->btn_1->sprite = create_sprite("assets/btn_1.png", NULL, 0.3, 0.3);
    sfSprite_setOrigin(game->btn_1->sprite, (sfVector2f){512, 512});
    game->btn_1->pos = (sfVector2f){160, 790};
    sfSprite_setPosition(game->btn_1->sprite, game->btn_1->pos);
    game->btn_2->sprite = create_sprite("assets/btn_2.png", NULL, 0.284, 0.284);
    sfSprite_setOrigin(game->btn_2->sprite, (sfVector2f){512, 512});
    game->btn_2->pos = (sfVector2f){330, 790};
    sfSprite_setPosition(game->btn_2->sprite, game->btn_2->pos);

    game->is_play = false;
    game->score = 0;
    game->high_score = 0;

    game->logo = create_sprite("assets/logo.png", NULL, 0.4, 0.4);
    sfSprite_setPosition(game->logo, (sfVector2f){50, 0});

    game->crosshair->sprite = create_sprite("assets/crosshair1.png", NULL, 0.15, 0.15);
    sfSprite_setOrigin(game->crosshair->sprite, (sfVector2f){250, 250});

    game->car->nb = 1;
    game->car->sprite = create_sprite(concat3("assets/Car_", int_to_str(game->car->nb), ".png"), NULL, 1, 1);
    game->car->pos = (sfVector2f){750, 400};
    sfSprite_setPosition(game->car->sprite, game->car->pos);

    game->music = sfMusic_createFromFile("sounds/song1.mp3");
    sfMusic_setVolume(game->music, 85.f);

    game->demo->sound = sfSound_create();
    sfSound_setVolume(game->demo->sound, 70.f);
    game->demo->buff = sfSoundBuffer_createFromFile("sounds/Demo.mp3");
    sfSound_setBuffer(game->demo->sound, game->demo->buff);

    game->save->sound = sfSound_create();
    sfSound_setVolume(game->save->sound, 80.f);
    game->save->buff = sfSoundBuffer_createFromFile("sounds/Save.mp3");
    sfSound_setBuffer(game->save->sound, game->save->buff);

    game->chat->clock = sfClock_create();
    game->chat->is_visible = false;
    game->chat->msg->sound = sfSound_create();
    sfSound_setVolume(game->chat->msg->sound, 80.f);
    game->chat->msg->buff = sfSoundBuffer_createFromFile("sounds/Chat.mp3");
    sfSound_setBuffer(game->chat->msg->sound, game->chat->msg->buff);
}

static void init_cars(car_t **car)
{
    for (int i = 0; i < NB_CAR; i++) {
        car_t *c = car[i];

        c->sprite = create_sprite("assets/Car_1.png", NULL, 0.25, 0.25);
        c->pos = (sfVector2f){400, rand() % 700 + 150};
        sfSprite_setOrigin(c->sprite, (sfVector2f){86.45, 45.5});
        sfSprite_setPosition(car[i]->sprite, car[i]->pos);

        c->ball->area = (sfIntRect){0, 0, 126, 149};
        c->ball->sprite = create_sprite("assets/Ball.png", &c->ball->area, 0.8, 0.8);
        c->ball->anim_clock = sfClock_create();
        c->speed = SPEED;
        c->boost->area = (sfIntRect){0, 0, 280, 200};
        c->boost->sprite =create_sprite("assets/boost.png", &c->boost->area, 0.4, 0.4);
        c->boost->anim_clock = sfClock_create();
        c->boost->is_visibe = false;
        c->sleep = 0.0;
        c->sleep_clock = sfClock_create();
        c->is_visible = true;
        wait_time(c);
    }
}

static void events(sfRenderWindow *window, game_t *game, car_t **car)
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

static void handle_death(sfRenderWindow *window, game_t *game, car_t **car)
{
    const sfTexture *tex = sfSprite_getTexture(game->background);
    sfVector2u sizeTex = sfTexture_getSize(tex);
    sfVector2f scale = sfSprite_getScale(game->background);
    float bgW = sizeTex.x * scale.x;

    game->life = 3;
    game->score = 0;
    game->is_play = false;
    for (int i = 0; i < NB_CAR; i++)
        car[i]->pos = (sfVector2f){bgW * 0.2f, rand() % 700 + 100};
    sfMusic_stop(game->music);
}

static void game_loop(sfRenderWindow *window, game_t *game, car_t **car)
{
    sfClock *clock = sfClock_create();

    while (sfRenderWindow_isOpen(window)) {
        sfTime dt = sfClock_restart(clock);
        events(window, game, car);
        if (game->life <= 0) {
            handle_death(window, game, car);
        }
        if (game->is_play) {
            update_cars(game, dt, car);
            update_highscore(game);
            display(window, game, car);
        } else if (!game->is_play){
            display_start(window, game);
        }
    }
    sfClock_destroy(clock);
}

static void cleanup_game(game_t *game, car_t **car)
{
    for (int i = 0; i < NB_CAR; i++) {
        if (car[i]->sprite)
            sfSprite_destroy(car[i]->sprite);
        if (car[i]->ball->anim_clock)
            sfClock_destroy(car[i]->ball->anim_clock);
        free(car[i]);
    }
    free(car);

    if (!game)
        return;
    if (game->background)
        sfSprite_destroy(game->background);

    if (game->start)
        sfSprite_destroy(game->start);

    if (game->btn && game->btn->sprite)
        sfSprite_destroy(game->btn->sprite);
    if (game->btn)
        free(game->btn);

    if (game->btn_1 && game->btn_1->sprite)
        sfSprite_destroy(game->btn_1->sprite);
    if (game->btn_1)
        free(game->btn_1);

    if (game->btn_2 && game->btn_2->sprite)
        sfSprite_destroy(game->btn_2->sprite);
    if (game->btn_2)
        free(game->btn_2);
    
    if (game->font)
        sfFont_destroy(game->font);
    if (game->text)
        sfText_destroy(game->text);
    
    if (game->crosshair)
        sfSprite_destroy(game->crosshair->sprite);
    free(game);
}

int main(void)
{
    srand(time(NULL));

    sfVideoMode mode = {1920, 1080};
    sfRenderWindow *window = sfRenderWindow_create(mode, "Pocket League", sfDefaultStyle | sfResize | sfClose, NULL);

    game_t *game = malloc(sizeof(game_t));
    if (!game)
        return EXIT_ERROR;
    game->btn = malloc(sizeof(btn_t));
    game->btn_1 = malloc(sizeof(btn_t));
    game->btn_2 = malloc(sizeof(btn_t));
    game->car = malloc(sizeof(car_sprite_t));
    game->demo = malloc(sizeof(sound_t));
    game->save = malloc(sizeof(sound_t));
    game->crosshair = malloc(sizeof(crosshair_t));
    game->chat = malloc(sizeof(chat_t));
    game->chat->msg = malloc(sizeof(sound_t));

    car_t **car = malloc(sizeof(car_t *) * NB_CAR);
    for (int i = 0; i < NB_CAR; i++) {
        car[i] = malloc(sizeof(car_t));
        car[i]->ball = malloc(sizeof(ball_t));
        car[i]->boost = malloc(sizeof(boost_t));
    }

    init_game(game);
    init_cars(car);

    game_loop(window, game, car);
    cleanup_game(game, car);
    sfRenderWindow_destroy(window);
    return EXIT_SUCCESS;
}
