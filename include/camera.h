#pragma once
#include "common.h"

typedef enum CAM_INFO 
{
    POS,
    PAST_POS,
    FORWARD,
    UP,
    RIGHT,
    LEFT
} CAM_INFO;

// 3D Version
extern Vec3 Cam_Info_ECS[6];
typedef struct TrackedCam
{
        Vec3 past_pos;
        Vec3 pos;
        Vec3 up;
        Vec3 right;
        Vec3 forward;
        Camera3D cam;
} TrackedCam;

Camera3D init_cam(const Vec3 pos, const Vec3 target, const Vec3 up, const float fovy) {
    Camera3D cam = {0};
    cam.target = target;
    cam.position = pos;
    cam.projection = CAMERA_PERSPECTIVE;
    cam.up = up;
    cam.fovy = fovy;
    return cam;
}

Vec3 get_forward(const Camera3D cam) {
    return Vector3Subtract(cam.target, cam.position);
}
Vec3 get_flat(Vec3 v)
{
    return (Vec3){v.x, .y = 0, .z = v.z};
}
Vec3 get_flat_forward(const Camera3D cam) {
    const Vec3 fwd = get_forward(cam);
    return (Vec3){fwd.x, 0, fwd.z};
}

Vec3 get_right(const Camera3D cam) {
    return Vector3CrossProduct(get_forward(cam), cam.up);
}


void update_cam(Camera3D* cam, const Vec3 target, const Vec3 pos)
{
    cam->position = pos;
    cam->target = target;
}

TrackedCam get_TrackedCam(Vec3 pos, Vec3 target, Vec3 up, float fovy)
{
    TrackedCam cam = {0};
    cam.cam = init_cam(pos, target, up, fovy);
    cam.forward = get_forward(cam.cam);
    cam.up = up;
    cam.right = get_right(cam.cam);
    cam.past_pos = pos;
    return cam;
}

void update_TrackedCam(TrackedCam* cam, Vec3 target, const Vec3 position_transformation)
{
    cam->past_pos = cam->pos;
    cam->pos = cam->cam.position;
    cam->forward = get_forward(cam->cam);
    cam->right = get_right(cam->cam);
    update_cam(&cam->cam, target, position_transformation);
}

Vec3 ZOOM_IN(Vec3 offset, float amount);
Vec3 ZOOM_IN(Vec3 offset, float amount)
{
    float sign_x, sign_y, sign_z;
    sign_x = SIGN_OF(offset.x);
    sign_y = SIGN_OF(offset.y);
    sign_z = SIGN_OF(offset.z);
    Vec3 zoomed = {
        .x = offset.x - (amount*sign_x), 
        .y = offset.y - (amount*sign_y), 
        .z = offset.z - (amount*sign_z) 
    };
    return zoomed;
}
Vec3 ZOOM_OUT(Vec3 offset, float amount);
Vec3 ZOOM_OUT(Vec3 offset, float amount)
{
    return ZOOM_IN(offset, -amount);
}
