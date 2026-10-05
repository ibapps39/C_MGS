#pragma once

#include "common.h"
#include "camera.h"
#include "movement.h"
#include "file_directory_managment.h"
#include "structures.h"


typedef struct Game_t
{
    Vec3 camera3d_offset;
    TrackedCam tracked_cam;
    Player player;
} Game;

extern Game GAME;

void INIT(Game* g)
{
    // Player transform & property configuration
    float player_move_speed = 50.0f;
    Vec3 init_player_pos = (Vec3){.x = 0, .y = 0, .z = 10};
    Vec3 player_fwd = (Vec3){.x = 100, .y = 0, .z = 0};
    Vec3 player_size = (Vec3){.x = 1, .y = 1, .z = 1};

    // Asset file paths inside resources/IQMTest/
    const char* texture_path = "resources/IQMTest/ElderJamPlayer.png";
    const char* model_path   = "resources/IQMTest/ElderJamPlayer.iqm";

    // 1. Load Texture and IQM Model
    Image img = LoadImage(texture_path);
    ImageResize(&img, 512, 512);
    Texture player_texture = LoadTexture(texture_path);
    Model player_model = LoadModel(model_path);

    // Bind texture directly to model material map 0 (Diffuse)
    player_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = player_texture;

    // 2. Load Animations from IQM model file
    int anim_count = 0;
    ModelAnimation* player_anime = LoadModelAnimations(model_path, &anim_count);

    // 3. Construct Player
    Player player = get_player(
        player_move_speed, 
        init_player_pos, 
        player_fwd, 
        player_texture, 
        player_model, 
        player_anime, 
        player_size
    );

    // 4. Setup Camera and TrackedCam
    Vec3 camera3d_offset = (Vec3){.x = 10, .y = 10, .z = -10};
    Vec3 initial_cam_pos = camera3d_offset;
    Vec3 cam_target      = init_player_pos;
    Vec3 cam_up          = (Vec3){.x = 0, .y = 1, .z = 0};
    float cam_fovy       = 120.0f;

    TrackedCam tc = get_TrackedCam(initial_cam_pos, cam_target, cam_up, cam_fovy);
    // 5. Store in Game state
    g->camera3d_offset = camera3d_offset;
    g->player          = player;
    g->tracked_cam     = tc;
}

void CONTROL_FLOW(Game* g, float dt)
{
    // Movement
    static bool rotated = false;

    if (IsKeyDown(KEY_LEFT))
    {
        g->tracked_cam.cam.position = Vector3RotateByAxisAngle(g->tracked_cam.cam.position, g->tracked_cam.up, DEG2RAD);
        g->camera3d_offset = Vector3RotateByAxisAngle(g->camera3d_offset, g->tracked_cam.up, DEG2RAD);
        rotated = true;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        g->tracked_cam.cam.position = Vector3RotateByAxisAngle(g->tracked_cam.cam.position, g->tracked_cam.up, -DEG2RAD);
        g->camera3d_offset = Vector3RotateByAxisAngle(g->camera3d_offset, g->tracked_cam.up, -DEG2RAD);
        rotated = true;
    }

    if (COMMON_MOVE_KEY_DOWN)
    {
        Vec3 fwd = get_flat_forward(g->tracked_cam.cam);
        g->player.fwd_v = fwd;
    }
    if (IsKeyPressed(KEY_Q)) 
    {
        g->tracked_cam.pos = (Vec3){10};
        g->player.pos = (Vec3){0};
        g->tracked_cam.cam.target = g->player.pos;
        g->tracked_cam.cam.position = (Vec3){10};
    }
    move(&g->player.pos, &g->tracked_cam, g->player.fwd_v, g->player.move_speed * dt);
    update_TrackedCam(&g->tracked_cam, g->player.pos, Vector3Add(g->player.pos, g->camera3d_offset));
    rotated = false;
}