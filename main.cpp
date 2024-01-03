#include "raylib.h"
#include <iostream>

using namespace std;

#define scr_width 720
#define scr_height 720

int side_hit_amount;

struct Logo {
    Texture2D texture;
    Vector2 pos;
    Vector2 vel;
    float scale;
    float speed;
    Color col;
};


void change_color(Logo * dvd) {
    dvd->col = Color{
        (unsigned char)GetRandomValue(0,255),
        (unsigned char)GetRandomValue(0,255),
        (unsigned char)GetRandomValue(0,255),
        255
        };
}

bool is_hitting_sides(Logo * dvd) {
    if (dvd->pos.x >= GetScreenWidth() - dvd->texture.width * dvd->scale
    || dvd->pos.y <= 0
    || dvd->pos.x <= 0
    || dvd->pos.y >= GetScreenHeight() - dvd->texture.height * dvd->scale) {
        return true;
    } else {
        return false;
    }
}

Vector2 set_direction(Logo * dvd) {
    
    if (dvd->pos.x >= GetScreenWidth() - dvd->texture.width * dvd->scale) {
        dvd->vel.x *= -1;
        change_color(dvd);
        side_hit_amount++;

    }
    if (dvd->pos.y <= 0) {
        dvd->vel.y *= -1;
        change_color(dvd);
        side_hit_amount++;

    }
    if (dvd->pos.x <= 0) {
        dvd->vel.x *= -1;
        change_color(dvd);
        side_hit_amount++;

    }
    if (dvd->pos.y >= GetScreenHeight() - dvd->texture.height * dvd->scale) {
        dvd->vel.y *= -1;
        change_color(dvd);
        side_hit_amount++;

    }

}

int main() {
    side_hit_amount = 0;

    InitWindow(scr_width,scr_height, "Raylib DVD Logo");
    InitAudioDevice();

    Sound hit_sound = LoadSound("assets/hit_sound.wav");

    Logo dvd = Logo();

    dvd.texture = LoadTexture("assets/dvd_logo.png");
    dvd.pos = Vector2{scr_width/2, scr_height/2};
    dvd.vel = Vector2{1,-1};
    dvd.scale = 0.1;
    dvd.speed = 150;
    dvd.col = GREEN;


    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
    
        dvd.pos.x += dvd.vel.x * dvd.speed * delta;
        dvd.pos.y += dvd.vel.y * dvd.speed * delta;

        set_direction(&dvd);

        if (IsKeyDown(KEY_UP) || GetMouseWheelMove() >= 1) {
            dvd.speed++;
        } else if ((IsKeyDown(KEY_DOWN) || GetMouseWheelMove() <= -1) && dvd.speed >= 1){
            dvd.speed--;
        } 

        if (is_hitting_sides(&dvd)) {
            PlaySound(hit_sound);

        }

        BeginDrawing();

            ClearBackground(BLACK);
            DrawTextureEx(dvd.texture, dvd.pos, 0, dvd.scale, dvd.col);
            DrawText(TextFormat("DVD Speed: %.2f", dvd.speed), 10, 10 ,20,RED);
            DrawText(TextFormat("Side Hit Amount: %d", side_hit_amount), 10, 30 ,20,RED);
        EndDrawing(); 
    
    }
}