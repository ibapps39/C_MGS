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

void INIT(Game *g)
{
    // Player transform & property configuration
    float player_move_speed = 50.0f;
    Vec3 init_player_pos = (Vec3){.x = 0, .y = 0, .z = 10};
    Vec3 player_fwd = (Vec3){.x = 1, .y = 0, .z = 0};
    Vec3 player_size = (Vec3){.x = 1, .y = 1, .z = 1};

    // Asset file paths inside resources/IQMTest/
    const char *texture_path = "./resources/IQMTest/models/ElderJamPlayer.png";
    const char *model_path = "./resources/IQMTest/models/ElderJamPlayer.iqm";

    // 1. Load Texture and IQM Model
    Texture player_texture = LoadTexture(texture_path);
    Model player_model = LoadModel(model_path);

    // Flip since blender is z up
    // We our character to be rotated -90 around x, and to rotate around the y to face the same direction as we move
    player_model.transform = MatrixRotateX(-90 * DEG2RAD);
    // Bind texture directly to model material
    player_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = player_texture;
    TraceLog(LOG_INFO, "meshes=%d materials=%d", player_model.meshCount, player_model.materialCount);
    TraceLog(LOG_INFO, "tex id=%d %dx%d", player_texture.id, player_texture.width, player_texture.height);

    // 2. Load Animations from IQM model file
    int anim_count = 0;
    ModelAnimation *player_anime = LoadModelAnimations(model_path, &anim_count);

    // 3. Construct Player
    Player player = get_player(
        player_move_speed,
        init_player_pos,
        player_fwd,
        player_texture,
        player_model,
        player_anime,
        player_size);

    // 4. Setup Camera and TrackedCam
    Vec3 camera3d_offset = (Vec3){.x = 10, .y = 10, .z = -10};
    Vec3 initial_cam_pos = camera3d_offset;
    Vec3 cam_target = init_player_pos;
    Vec3 cam_up = (Vec3){.x = 0, .y = 1, .z = 0};
    float cam_fovy = 120.0f;

    TrackedCam tc = get_TrackedCam(initial_cam_pos, cam_target, cam_up, cam_fovy);
    // 5. Store in Game state
    g->camera3d_offset = camera3d_offset;
    g->player = player;
    g->tracked_cam = tc;
}

void CONTROL_FLOW(Game *g, float dt)
{
    // Movement
    static bool rotated = false;

    const Vec3 before = g->player.pos;
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

    if (IsKeyPressed(KEY_Q))
    {
        g->tracked_cam.pos = (Vec3){10};
        g->player.pos = (Vec3){0};
        g->tracked_cam.cam.target = g->player.pos;
        g->tracked_cam.cam.position = (Vec3){10};
    }
    if (IsKeyDown(KEY_UP))
        g->camera3d_offset = ZOOM_IN(g->camera3d_offset, 1.00f);
    if (IsKeyDown(KEY_DOWN))
        g->camera3d_offset = ZOOM_OUT(g->camera3d_offset, 1.00f);
    move(&g->player.pos, get_flat(g->tracked_cam.right), get_flat_forward(g->tracked_cam.cam), g->player.move_speed * dt);
    update_TrackedCam(&g->tracked_cam, g->player.pos, Vector3Add(g->player.pos, g->camera3d_offset));
    const Vec3 delta = Vector3Subtract(g->player.pos, before);
    if(Vector3LengthSqr(delta) > 0)
    {
        g->player.fwd_v = delta;
    }
    rotated = false;
}