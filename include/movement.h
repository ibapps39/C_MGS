#pragma once
#include "common.h"
#include "camera.h"



Vec3 get_flat_right_norm(const Camera3D cam) {
    Vec3 v = Vector3CrossProduct(get_flat_forward(cam), cam.up);
    v =  Vector3Normalize(v);
    v.y = 0;
    return v;
}


void move(Vec3* p, TrackedCam* cam, Vector3 fwd, float move_speed)
{
    Vec3 forward = fwd;
    forward.y = 0;
    forward = Vector3Normalize(fwd);
    Vec3 right = Vector3Normalize(cam->right);
    right.y = 0;
    right = Vector3Normalize(right);

    // --- Movement ---
    Vector3 dir = { 0 };
    if (IsKeyDown(KEY_W)) dir = Vector3Add(dir, forward);                 // away from cam
    if (IsKeyDown(KEY_S)) dir = Vector3Subtract(dir, forward);            // towards cam
    if (IsKeyDown(KEY_A)) dir = Vector3Subtract(dir, right);                  
    if (IsKeyDown(KEY_D)) dir = Vector3Add(dir, right);          

    Vec3 scaled = Vector3Scale(dir, move_speed);
    *p = Vector3Add(*p, scaled);
}
