#include "common.h"
#include "camera.h"
#include "movement.h"
#include "file_directory_managment.h"
#include "structures.h"
#include "Game.h"

#define VIRT_WIDTH 600
#define VIRT_HEIGHT 600
#define DEFAULT_FPS 60
#define BG_COLOR BLACK
#define UP (Vec3){0, 1, 0}

Game GAME;

int main(void)
{

        int SCREEN_W = VIRT_WIDTH;
        int SCREEN_H = VIRT_HEIGHT;
        int TARGET_FPS = DEFAULT_FPS;
        InitWindow(SCREEN_W, SCREEN_H, "Raylib_Template");
        SetWindowState(FLAG_WINDOW_RESIZABLE);
        SetTargetFPS(TARGET_FPS);

        ChangeDirectory(GetApplicationDirectory());
        const char *RESOURCES_PATH = "./resources/";
        INIT(&GAME);
        Player *p = &GAME.player;
        
        while (!WindowShouldClose())
        {
                float dt = GetFrameTime();
                int H = GetScreenHeight();
                int W = GetScreenWidth();
                const float time_passed = GetTime();

                CONTROL_FLOW(&GAME, dt);
                
                static float yaw = 0.0f;
                // if (Vector3LengthSqr(p->fwd_v) < 1)
                // {
                //         yaw = atan2f(MODEL_TURN_DIR.x, MODEL_TURN_DIR.z) * RAD2DEG;
                // }
                const Vec3 pfv = Vector3Normalize(p->fwd_v);
                yaw = atan2f(pfv.x, pfv.z) * RAD2DEG;
                BeginDrawing();
                ClearBackground(BG_COLOR);
                BeginMode3D(GAME.tracked_cam.cam);
                DrawGrid(10, 10.0f);
                // DrawModel(p->model, p->pos, 1, WHITE);
                static float angle = 0.0f;
                if (IsKeyDown(KEY_G))
                {
                        angle -= 1;
                        TraceLog(LOG_INFO, "angle %.2f\n", angle);
                }
                if (IsKeyDown(KEY_F))
                {
                        angle += 1;
                        TraceLog(LOG_INFO, "angle %.2f\n", angle);
                }
                static int ani = 0;
                if(COMMON_MOVE_KEY_DOWN) { ani++; ani = ani%p->m_anime->keyframeCount; } else {ani = 0;}
                
                DrawModelEx(p->model, p->pos, (Vector3){0.0f, 1.0f, 0.0f}, yaw, (Vec3){0.1, 0.1, 0.1}, WHITE);
                DrawBoundingBox(GetModelBoundingBox(GAME.player.model), RED);
                Ray r = {.position = p->pos, .direction = p->fwd_v};
                DrawRay(r, PINK);
                EndMode3D();
                EndDrawing();
        }
        UnloadTexture(GAME.player.model.materials->maps->texture);
        UnloadModel(GAME.player.model);
        CloseWindow();
        return 0;
}
