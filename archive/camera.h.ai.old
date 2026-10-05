#pragma once
#include "common.h" // raylib.h + raymath.h + Vec3

// Cam3D / Cam2D never read a device. They take a CamInput (plain floats),
// and cam_input_read() fills it from the macros below. To use another
// framework or a different device, change the MOV_CAM_* macros (or just fill a
// CamInput yourself and skip cam_input_read entirely).
//
//   CamInput in = cam_input_read();
//   cam3d_update(&cam3d, in, dt);
//   cam2d_update(&cam2d, in, dt);
//
// Conventions: forward+ right+ up+, pitch+ = look up, yaw+ = turn left, zoom+ = in

// ---- keyboard bindings (override with -D or #define before including) -------
#ifndef MOV_FORWARD_KEY
#define MOV_FORWARD_KEY    KEY_W
#endif
#ifndef MOV_BACKWARD_KEY
#define MOV_BACKWARD_KEY   KEY_S
#endif
#ifndef MOV_LEFT_KEY
#define MOV_LEFT_KEY       KEY_A
#endif
#ifndef MOV_RIGHT_KEY
#define MOV_RIGHT_KEY      KEY_D
#endif
#ifndef MOV_UP_KEY
#define MOV_UP_KEY         KEY_E
#endif
#ifndef MOV_DOWN_KEY
#define MOV_DOWN_KEY       KEY_Q
#endif
#ifndef TILT_CAM_UP_KEY
#define TILT_CAM_UP_KEY    KEY_UP
#endif
#ifndef TILT_CAM_DOWN_KEY
#define TILT_CAM_DOWN_KEY  KEY_DOWN
#endif
#ifndef TURN_CAM_LEFT_KEY
#define TURN_CAM_LEFT_KEY  KEY_LEFT
#endif
#ifndef TURN_CAM_RIGHT_KEY
#define TURN_CAM_RIGHT_KEY KEY_RIGHT
#endif
#ifndef ZOOM_IN_KEY
#define ZOOM_IN_KEY        KEY_EQUAL
#endif
#ifndef ZOOM_OUT_KEY
#define ZOOM_OUT_KEY       KEY_MINUS
#endif

// ---- gamepad bindings: dpad moves, face buttons look, triggers fly, bumpers zoom
// -1 = unbound. Set CAM_PAD to -1 to turn the gamepad off completely.
#ifndef CAM_PAD
#define CAM_PAD 0
#endif
#ifndef MOV_FORWARD_BTN
#define MOV_FORWARD_BTN    GAMEPAD_BUTTON_LEFT_FACE_UP
#endif
#ifndef MOV_BACKWARD_BTN
#define MOV_BACKWARD_BTN   GAMEPAD_BUTTON_LEFT_FACE_DOWN
#endif
#ifndef MOV_LEFT_BTN
#define MOV_LEFT_BTN       GAMEPAD_BUTTON_LEFT_FACE_LEFT
#endif
#ifndef MOV_RIGHT_BTN
#define MOV_RIGHT_BTN      GAMEPAD_BUTTON_LEFT_FACE_RIGHT
#endif
#ifndef MOV_UP_BTN
#define MOV_UP_BTN         GAMEPAD_BUTTON_RIGHT_TRIGGER_2
#endif
#ifndef MOV_DOWN_BTN
#define MOV_DOWN_BTN       GAMEPAD_BUTTON_LEFT_TRIGGER_2
#endif
#ifndef TILT_CAM_UP_BTN
#define TILT_CAM_UP_BTN    GAMEPAD_BUTTON_RIGHT_FACE_UP
#endif
#ifndef TILT_CAM_DOWN_BTN
#define TILT_CAM_DOWN_BTN  GAMEPAD_BUTTON_RIGHT_FACE_DOWN
#endif
#ifndef TURN_CAM_LEFT_BTN
#define TURN_CAM_LEFT_BTN  GAMEPAD_BUTTON_RIGHT_FACE_LEFT
#endif
#ifndef TURN_CAM_RIGHT_BTN
#define TURN_CAM_RIGHT_BTN GAMEPAD_BUTTON_RIGHT_FACE_RIGHT
#endif
#ifndef ZOOM_IN_BTN
#define ZOOM_IN_BTN        GAMEPAD_BUTTON_RIGHT_TRIGGER_1
#endif
#ifndef ZOOM_OUT_BTN
#define ZOOM_OUT_BTN       GAMEPAD_BUTTON_LEFT_TRIGGER_1
#endif

// ---- the device layer: this is the part to swap for another framework -------
#define CAM_KEY_DOWN(key) ((key) != KEY_NULL && IsKeyDown(key))
#define CAM_BTN_DOWN(btn) (CAM_PAD >= 0 && (btn) >= 0 && IsGamepadAvailable(CAM_PAD) && IsGamepadButtonDown(CAM_PAD, btn))

#define MOV_CAM_FORWARD  (CAM_KEY_DOWN(MOV_FORWARD_KEY)    || CAM_BTN_DOWN(MOV_FORWARD_BTN))
#define MOV_CAM_BACK     (CAM_KEY_DOWN(MOV_BACKWARD_KEY)   || CAM_BTN_DOWN(MOV_BACKWARD_BTN))
#define MOV_CAM_LEFT     (CAM_KEY_DOWN(MOV_LEFT_KEY)       || CAM_BTN_DOWN(MOV_LEFT_BTN))
#define MOV_CAM_RIGHT    (CAM_KEY_DOWN(MOV_RIGHT_KEY)      || CAM_BTN_DOWN(MOV_RIGHT_BTN))
#define MOV_CAM_UP       (CAM_KEY_DOWN(MOV_UP_KEY)         || CAM_BTN_DOWN(MOV_UP_BTN))
#define MOV_CAM_DOWN     (CAM_KEY_DOWN(MOV_DOWN_KEY)       || CAM_BTN_DOWN(MOV_DOWN_BTN))
#define TILT_CAM_UP    (CAM_KEY_DOWN(TILT_CAM_UP_KEY)    || CAM_BTN_DOWN(TILT_CAM_UP_BTN))
#define TILT_CAM_DOWN  (CAM_KEY_DOWN(TILT_CAM_DOWN_KEY)  || CAM_BTN_DOWN(TILT_CAM_DOWN_BTN))
#define TURN_CAM_LEFT  (CAM_KEY_DOWN(TURN_CAM_LEFT_KEY)  || CAM_BTN_DOWN(TURN_CAM_LEFT_BTN))
#define TURN_CAM_RIGHT (CAM_KEY_DOWN(TURN_CAM_RIGHT_KEY) || CAM_BTN_DOWN(TURN_CAM_RIGHT_BTN))
#define ZOOMOV_CAM_IN    (CAM_KEY_DOWN(ZOOM_IN_KEY)        || CAM_BTN_DOWN(ZOOM_IN_BTN))
#define ZOOMOV_CAM_OUT   (CAM_KEY_DOWN(ZOOM_OUT_KEY)       || CAM_BTN_DOWN(ZOOM_OUT_BTN))


#ifndef CAM_MOVE_SPEED
#define CAM_MOVE_SPEED   100.0f     // 3D: world units / s
#endif
#ifndef CAM_TURN_SPEED
#define CAM_TURN_SPEED   2.2f     // rad / s
#endif
#ifndef CAM_PAN_SPEED
#define CAM_PAN_SPEED    400.0f   // 2D: screen px / s
#endif
#ifndef CAM_ZOOM_SPEED
#define CAM_ZOOM_SPEED   2.0f     // 2D: ln(zoom) / s
#endif
#ifndef CAM_WHEEL_STEP
#define CAM_WHEEL_STEP   0.2f     // 2D: ln(zoom) per wheel notch, about 1.22x
#endif
#ifndef CAM_ZOOM_MIN
#define CAM_ZOOM_MIN     0.05f
#endif
#ifndef CAM_ZOOM_MAX
#define CAM_ZOOM_MAX     20.0f
#endif
#ifndef CAM_DEADZONE
#define CAM_DEADZONE     0.15f    // gamepad sticks
#endif

// ---- input ------------------------------------------------------------------

// each axis is -1..1
typedef struct CamInput
{
    float forward, right, up;
    float pitch, yaw;
    float zoom;
} CamInput;

CamInput cam_input_read(void);                            // keys/buttons + left/right stick
CamInput cam_input_mouse_look(CamInput in, float sens);   // optional, DisableCursor() first. sens ~0.002

// ---- 3D ---------------------------------------------------------------------

typedef enum CamMoveMode
{
    CAM_MOVE_FLY,   // W/S along view dir (follows pitch), A/D strafe, Q/E along cam up
    CAM_MOVE_FLAT,  // FPS: W/S along the ground, A/D strafe, Q/E world up/down
    CAM_MOVE_PAN,   // editor: W/S slide along cam up, A/D along cam right
} CamMoveMode;

typedef struct Cam3D
{
    Camera3D    base_cam;
    float       move_speed;   // units / s
    float       turn_speed;   // rad / s
    float       pitch_limit;  // rad away from straight up/down, 0 = no limit. e.g. 85*DEG2RAD
    CamMoveMode mode;
} Cam3D;

// ---- 2D ---------------------------------------------------------------------

typedef struct Cam2D
{
    Camera2D base_cam;
    float    move_speed;  // screen px / s
    float    turn_speed;  // rad / s
    float    zoom_speed;  // ln(zoom) / s
    float    zoom_min;
    float    zoom_max;
} Cam2D;

Cam2D cam2d_make(Vec2 screen_center);
void  cam2d_update(Cam2D* cam, CamInput in, float dt);
void  cam2d_zoom_wheel(Cam2D* cam, float wheel);   // cam2d_zoom_wheel(&cam2d, GetMouseWheelMove());

// pure
Camera2D cam2d_pan(Camera2D cam, Vec2 screen_delta);
Camera2D cam2d_zoomed(Camera2D cam, float ln_zoom, float zoom_min, float zoom_max);
Camera2D cam2d_rotated(Camera2D cam, float yaw);

// ---- small helpers, you might both want them -------
float cam_axis(bool neg, bool pos);   // -1, 0 or 1
float cam_deadzone(float v);          // 0 if the stick is barely off center

// ---- input ------------------------------------------------------------------

float cam_axis(bool neg, bool pos)
{
    return (float)pos - (float)neg;
}

float cam_deadzone(float v)
{
    return fabsf(v) < CAM_DEADZONE ? 0.0f : v;
}

CamInput cam_input_read(void)
{
    CamInput in = { 0 };
    in.forward = cam_axis(MOV_CAM_BACK,     MOV_CAM_FORWARD);
    in.right   = cam_axis(MOV_CAM_LEFT,     MOV_CAM_RIGHT);
    in.up      = cam_axis(MOV_CAM_DOWN,     MOV_CAM_UP);
    in.pitch   = cam_axis(TILT_CAM_DOWN,  TILT_CAM_UP);
    in.yaw     = cam_axis(TURN_CAM_RIGHT, TURN_CAM_LEFT);
    in.zoom    = cam_axis(ZOOMOV_CAM_OUT,   ZOOMOV_CAM_IN);

    // sticks add on top of the buttons: left = move, right = look
    if (CAM_PAD >= 0 && IsGamepadAvailable(CAM_PAD)) {
        in.forward += cam_deadzone(-GetGamepadAxisMovement(CAM_PAD, GAMEPAD_AXIS_LEFT_Y));   // stick up = forward
        in.right   += cam_deadzone( GetGamepadAxisMovement(CAM_PAD, GAMEPAD_AXIS_LEFT_X));
        in.yaw     += cam_deadzone(-GetGamepadAxisMovement(CAM_PAD, GAMEPAD_AXIS_RIGHT_X));  // stick right = turn right
        in.pitch   += cam_deadzone(-GetGamepadAxisMovement(CAM_PAD, GAMEPAD_AXIS_RIGHT_Y));  // stick up = look up
    }

    in.forward = Clamp(in.forward, -1.0f, 1.0f);
    in.right   = Clamp(in.right,   -1.0f, 1.0f);
    in.yaw     = Clamp(in.yaw,     -1.0f, 1.0f);
    in.pitch   = Clamp(in.pitch,   -1.0f, 1.0f);
    return in;
}

CamInput cam_input_mouse_look(CamInput in, float sens)
{
    Vec2 delta = GetMouseDelta();
    in.yaw   -= delta.x * sens;  // mouse right -> turn right
    in.pitch -= delta.y * sens;  // mouse up    -> look up
    return in;
}

// ---- 3D ---------------------------------------------------------------------

Cam3D cam3d_make(Vec3 pos, Vec3 target, Vec3 up, float fovy, float move_speed, float turn_speed, float pitch_limit, CamMoveMode cam_mode)
{
    Cam3D cam = { 0 };
    cam.base_cam.position   = pos;
    cam.base_cam.target     = target;
    cam.base_cam.up         = up;
    cam.base_cam.fovy       = fovy;
    cam.base_cam.projection = CAMERA_PERSPECTIVE;
    cam.move_speed  = move_speed;
    cam.turn_speed  = turn_speed;
    cam.pitch_limit = pitch_limit;
    cam.mode        = cam_mode;
    return cam;
}

Vec3 cam3d_forward(Camera3D cam)
{
    return Vector3Normalize(Vector3Subtract(cam.target, cam.position));
}

// looking straight up/down makes this zero (forward and up are parallel).
// pitch_limit keeps you out of there
Vec3 cam3d_right(Camera3D cam)
{
    return Vector3Normalize(Vector3CrossProduct(cam3d_forward(cam), cam.up));
}

Vec3 cam3d_move_vec(Camera3D cam, CamInput in, CamMoveMode mode, float speed, float dt)
{
    Vec3 forward = cam3d_forward(cam);
    Vec3 right   = cam3d_right(cam);
    Vec3 up      = Vector3CrossProduct(right, forward); // the camera's up, not world up
    Vec3 move    = { 0 };

    if (mode == CAM_MOVE_FLY) {
        move = Vector3Add(Vector3Scale(forward, in.forward), Vector3Scale(right, in.right));
        move = Vector3Add(move, Vector3Scale(up, in.up));
    }
    else if (mode == CAM_MOVE_FLAT) {
        // forward with the up part removed, so looking down doesn't dig you into the floor
        Vec3 flat_forward = Vector3Subtract(forward, Vector3Scale(cam.up, Vector3DotProduct(forward, cam.up)));
        flat_forward = Vector3Normalize(flat_forward);
        Vec3 flat_right = Vector3CrossProduct(flat_forward, cam.up);
        move = Vector3Add(Vector3Scale(flat_forward, in.forward), Vector3Scale(flat_right, in.right));
        move = Vector3Add(move, Vector3Scale(cam.up, in.up));
    }
    else { // CAM_MOVE_PAN
        move = Vector3Add(Vector3Scale(right, in.right), Vector3Scale(up, in.forward));
    }

    return Vector3Scale(move, speed * dt);
}

// position and target move together, so the view direction stays the same
Camera3D cam3d_moved(Camera3D cam, Vec3 delta)
{
    cam.position = Vector3Add(cam.position, delta);
    cam.target   = Vector3Add(cam.target,   delta);
    return cam;
}

Camera3D cam3d_rotated(Camera3D cam, float yaw, float pitch)
{
    if (yaw == 0.0f && pitch == 0.0f) return cam;

    Vec3 forward = cam3d_forward(cam);

    // yaw first, around up, so pitch's "right" axis is computed post-yaw
    if (yaw != 0.0f)
        forward = Vector3RotateByAxisAngle(forward, cam.up, yaw);
    if (pitch != 0.0f) {
        Vec3 right = Vector3Normalize(Vector3CrossProduct(forward, cam.up));
        forward = Vector3RotateByAxisAngle(forward, right, pitch);
    }

    cam.target = Vector3Add(cam.position, forward);
    return cam;
}

// same, but pitch stops `limit` rad short of straight up/down
Camera3D cam3d_rotated_clamped(Camera3D cam, float yaw, float pitch, float limit)
{
    cam = cam3d_rotated(cam, yaw, 0.0f);
    if (pitch == 0.0f) return cam;

    // angle between forward and up: 0 = looking straight up, PI = straight down
    float angle = acosf(Clamp(Vector3DotProduct(cam3d_forward(cam), Vector3Normalize(cam.up)), -1.0f, 1.0f));
    pitch = Clamp(pitch, angle - (PI - limit), angle - limit);
    return cam3d_rotated(cam, 0.0f, pitch);
}

void cam3d_update(Cam3D* cam, CamInput in, float dt)
{
    float yaw   = in.yaw   * cam->turn_speed * dt;
    float pitch = in.pitch * cam->turn_speed * dt;

    Vec3 move = cam3d_move_vec(cam->base_cam, in, cam->mode, cam->move_speed, dt);
    cam->base_cam = cam3d_moved(cam->base_cam, move);

    if (cam->pitch_limit > 0.0f) cam->base_cam = cam3d_rotated_clamped(cam->base_cam, yaw, pitch, cam->pitch_limit);
    else                         cam->base_cam = cam3d_rotated(cam->base_cam, yaw, pitch);
}

// ---- 2D (world +y is down on screen, like raylib) ---------------------------

Cam2D cam2d_make(Vec2 offset)
{
    Cam2D cam = { 0 };
    cam.base_cam.offset = offset;
    cam.base_cam.zoom   = 1.0f;
    cam.move_speed = CAM_PAN_SPEED;
    cam.turn_speed = CAM_TURN_SPEED;
    cam.zoom_speed = CAM_ZOOM_SPEED;
    cam.zoom_min   = CAM_ZOOM_MIN;
    cam.zoom_max   = CAM_ZOOM_MAX;
    return cam;
}

// screen_delta is in px (+x right, +y down). Undo the view rotation and zoom so
// "right" always means right on screen
Camera2D cam2d_pan(Camera2D cam, Vec2 screen_delta)
{
    float rad = -cam.rotation * DEG2RAD;
    float cs  = cosf(rad);
    float sn  = sinf(rad);
    Vec2 world = {
        (screen_delta.x * cs - screen_delta.y * sn) / cam.zoom,
        (screen_delta.x * sn + screen_delta.y * cs) / cam.zoom,
    };
    cam.target = Vector2Add(cam.target, world);
    return cam;
}

// zoom multiplies (exp) so it feels even and can never reach 0
Camera2D cam2d_zoomed(Camera2D cam, float ln_zoom, float zoom_min, float zoom_max)
{
    if (ln_zoom != 0.0f)
        cam.zoom = Clamp(cam.zoom * expf(ln_zoom), zoom_min, zoom_max);
    return cam;
}

// yaw in radians, + = counter-clockwise
Camera2D cam2d_rotated(Camera2D cam, float yaw)
{
    cam.rotation += yaw * RAD2DEG;
    return cam;
}

void cam2d_update(Cam2D* cam, CamInput in, float dt)
{
    Vec2 pan = { in.right * cam->move_speed * dt, -in.forward * cam->move_speed * dt };
    cam->base_cam = cam2d_pan(cam->base_cam, pan);
    cam->base_cam = cam2d_zoomed(cam->base_cam, in.zoom * cam->zoom_speed * dt, cam->zoom_min, cam->zoom_max);
    cam->base_cam = cam2d_rotated(cam->base_cam, in.yaw * cam->turn_speed * dt);
}

void cam2d_zoom_wheel(Cam2D* cam, float wheel)
{
    cam->base_cam = cam2d_zoomed(cam->base_cam, wheel * CAM_WHEEL_STEP, cam->zoom_min, cam->zoom_max);
}