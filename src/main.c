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

        while (!WindowShouldClose())
        {
                float dt = GetFrameTime();
                int H = GetScreenHeight();
                int W = GetScreenWidth();
                const float time_passed = GetTime();

                CONTROL_FLOW(&GAME, dt);
                
                BeginDrawing();
                ClearBackground(BG_COLOR);
                        BeginMode3D(GAME.tracked_cam.cam);
                                DrawGrid(10, 10.0f);
                                DrawModel(GAME.player.model, GAME.player.pos, 1.0f, WHITE);
                        EndMode3D();
                EndDrawing();
        }
        UnloadTexture(GAME.player.model.materials->maps->texture);
        UnloadModel(GAME.player.model);
        CloseWindow();
        return 0;
}
