#include "common.h"
#include "camera.h"
#include "movement.h"
#include "file_directory_managment.h"
#include "structures.h"

#define VIRT_WIDTH 600
#define VIRT_HEIGHT 600
#define DEFAULT_FPS 60
#define BG_COLOR BLACK

int main(void)
{

        int SCREEN_W = VIRT_WIDTH;
        int SCREEN_H = VIRT_HEIGHT;
        int TARGET_FPS = DEFAULT_FPS;
        const char *RESOURCES_PATH = "./resources/";

        InitWindow(SCREEN_W, SCREEN_H, "Raylib_Template");
        SetWindowState(FLAG_WINDOW_RESIZABLE);
        SetTargetFPS(TARGET_FPS);
        
        

        TrackedCam tracked_cam = get_TrackedCam(cam_pos, cam_target, cam_up, cam_fovy);
        Camera3D* cam = &tracked_cam.cam;
        TrackedCam* cam_tcp = &tracked_cam;
        Vec3 pos_delta = {-10, 10, 10};

        
        update_TrackedCam(cam_tcp, cube_pos, Vector3Add(cube_pos, pos_delta));


        while (!WindowShouldClose())
        {
                float dt = GetFrameTime();
                int H = GetScreenHeight();
                int W = GetScreenWidth();
                const float time_passed = GetTime();


                //

                BeginDrawing();
                ClearBackground(BG_COLOR);
                        BeginMode3D(*cam);
                                DrawGrid(10, 10.0f);
                                DrawCube(cube_pos, 2, 10, 2, WHITE);
                        EndMode3D();
                EndDrawing();
        }

        CloseWindow();
        return 0;
}
