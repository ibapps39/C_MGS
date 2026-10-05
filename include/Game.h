#pragma once

#include "common.h"
#include "camera.h"
#include "movement.h"
#include "file_directory_managment.h"
#include "structures.h"


typedef struct Game_t
{
    Vec3 pos_delta;
    TrackedCam tracked_cam;
    Player player;
} Game;

Game GAME;

void INITALIZATION(Game* g)
{

    Vec3 init_player_pos = (Vec3){.x = 0, .y = 0, .z = 10};
    Vec3 player_fwd = (Vec3){100,0,0};
    Vec3 player_size = (Vec3){.x = 1, .y = 1, .z = 1};
    Player player = (Player){0};
    const char* player_texture_path = "resources/player.png";
    const char* player_animations_path = "";
    Texture player_texture = LoadTexture(player_texture_path);
    Model player_model = LoadModel("resources/player.obj");
    // Load animations
    FilePathList player_anime_list = LoadDirectoryFiles(player_animations_path);
    ModelAnimation* player_anime = LoadModelAnimations(player_anime_list.paths[0], &player_anime_list.count);

    player = get_player(init_player_pos, player_fwd, player_texture, player_model, player_anime, player_size);

    Vec3 pos_delta = (Vec3){.x = -10, .y = 10, .z = -10};
    Vec3 initial_cam_pos = (Vec3){.x = 0, .y = 0, .z = 10};
    Vec3 cam_target = (Vec3){.x = 100, .y = , .z = -1};
    TrackedCam tc = get_TrackedCam(initial_cam_pos, cam_target, cam_up, cam_fovy);

    g->pos_delta = pos_delta;

}

void CONTROL_FLOW()
{
    // Movement
    static bool rotated = false;

    update_TrackedCam(cam_tcp, cube_pos, Vector3Add(cube_pos, pos_delta));
    if (IsKeyDown(KEY_LEFT))
    {
        cam->position = Vector3RotateByAxisAngle(cam->position, cam->up, DEG2RAD);
        pos_delta = Vector3RotateByAxisAngle(pos_delta, cam->up, DEG2RAD);
        rotated = true;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        cam->position = Vector3RotateByAxisAngle(cam->position, cam->up, -DEG2RAD);
        pos_delta = Vector3RotateByAxisAngle(pos_delta, cam->up, -DEG2RAD);
        rotated = true;
    }

    if (COMMON_MOVE_KEY_DOWN)
    {
        Vec3 fwd = get_flat_forward(*cam);
        fwd = Vector3Normalize(fwd);
        cube_forward_v = fwd;
    }
    move(cube_v, cam_tcp, cube_forward_v, mov_speed * dt);
    rotated = false;
}