/*
** EPITECH PROJECT, 2025
** G-MUL-100-BDX-1-1-myhunter-3
** File description:
** init
*/

#include "funct.h"

static void init_gtext(game_t *game)
{
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
}

static void init_gbtn(game_t *game)
{
    game->btn->sprite = create_sprite("assets/start_btn.png", NULL, 1, 1);
    sfSprite_setOrigin(game->btn->sprite, (sfVector2f){240, 135});
    game->btn->pos = (sfVector2f){250, 650};
    sfSprite_setPosition(game->btn->sprite, game->btn->pos);
    game->btn_1->sprite = create_sprite("assets/btn_1.png", NULL, 0.3, 0.3);
    sfSprite_setOrigin(game->btn_1->sprite, (sfVector2f){512, 512});
    game->btn_1->pos = (sfVector2f){160, 790};
    sfSprite_setPosition(game->btn_1->sprite, game->btn_1->pos);
    game->btn_2->sprite = create_sprite("assets/btn_2.png", NULL,
        0.284, 0.284);
    sfSprite_setOrigin(game->btn_2->sprite, (sfVector2f){512, 512});
    game->btn_2->pos = (sfVector2f){330, 790};
    sfSprite_setPosition(game->btn_2->sprite, game->btn_2->pos);
}

static void init_gsounds(game_t *game)
{
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

static void init_gexplo(game_t *game)
{
    if (!game->explo)
        exit(84);
    game->explo->area = (sfIntRect){0, 0, 350, 400};
    game->explo->sprite = create_sprite("assets/Demo.png", &game->explo->area,
        0.15, 0.15);
    game->explo->is_visible = false;
    game->explo->clock = sfClock_create();
}

static void init_gsprite(game_t *game)
{
    int map = rand() % 3 + 1;

    game->background = create_sprite(concat3("assets/Map_",
        int_to_str(map), ".png"), NULL, 1.428, 1.406);
    game->start = create_sprite("assets/start_screen.png", NULL, 1.428, 1.406);
    game->logo = create_sprite("assets/logo.png", NULL, 0.4, 0.4);
    sfSprite_setPosition(game->logo, (sfVector2f){50, 0});
    game->crosshair->sprite = create_sprite("assets/crosshair1.png", NULL,
        0.15, 0.15);
    sfSprite_setOrigin(game->crosshair->sprite, (sfVector2f){250, 250});
    game->car->sprite = create_sprite(concat3("assets/Car_",
        int_to_str(game->car->nb), ".png"), NULL, 1, 1);
    game->car->pos = (sfVector2f){750, 400};
    sfSprite_setPosition(game->car->sprite, game->car->pos);
    init_gexplo(game);
}

void init_game(game_t *game)
{
    game->life = 3;
    game->is_play = false;
    game->score = 0;
    game->high_score = 0;
    game->car->nb = 1;
    init_gtext(game);
    init_gbtn(game);
    init_gsprite(game);
    init_gsounds(game);
}

static void init_csprite(car_t *c)
{
    c->sprite = create_sprite("assets/Car_1.png", NULL, 0.25, 0.25);
    c->pos = (sfVector2f){400, rand() % 700 + 150};
    sfSprite_setOrigin(c->sprite, (sfVector2f){86.45, 45.5});
    sfSprite_setPosition(c->sprite, c->pos);
    c->ball->area = (sfIntRect){0, 0, 126, 149};
    c->ball->sprite = create_sprite("assets/Ball.png", &c->ball->area,
        0.8, 0.8);
    c->boost->area = (sfIntRect){0, 0, 280, 200};
    c->boost->sprite = create_sprite("assets/boost.png", &c->boost->area,
        0.4, 0.4);
}

void init_cars(car_t **car)
{
    car_t *c = NULL;

    for (int i = 0; i < NB_CAR; i++) {
        c = car[i];
        init_csprite(c);
        c->ball->anim_clock = sfClock_create();
        c->speed = SPEED;
        c->boost->anim_clock = sfClock_create();
        c->boost->is_visibe = false;
        c->sleep = 0.0;
        c->sleep_clock = sfClock_create();
        c->is_visible = true;
        wait_time(c);
    }
}
