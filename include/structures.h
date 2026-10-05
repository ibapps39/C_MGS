#pragma once
#include "stdio.h"
#include "common.h"

char *INFO_LABEL = "";
int INFO_NUM = 0;
float INFO_NUMF = 0.0f;
double INFO_NUMD = 0.00;
char *INFO_TEXT = "";

void DRAW_WHATEVER()
{
    const char *(*INFO_MSG)(char *, float) = TextFormat("%s : %.2f", INFO_LABEL, INFO_NUM);
    DrawText(INFO_MSG, 0, 0, 20, WHITE);
}

typedef struct PLAYER
{
    Vec3 fwd_v;
    Vec3 pos;
    Vec3 size;
    Texture texture;
    Model model;
    ModelAnimation* m_anime;
} Player;

Player get_player(Vec3 pos, Vec3 fwd, Texture player_texture, Model player_model, ModelAnimation* player_anime, Vec3 size)
{
    Player player = {0};
    player.fwd_v = fwd;
    player.pos = pos;
    player.texture = player_texture;
    player.size = size;
    player.model = player_model;
    player.m_anime = player_anime;
    return player;
}