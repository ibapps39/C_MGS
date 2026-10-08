#pragma once
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

typedef Vector2 Vec2;
typedef Vector3 Vec3;

#define SCREEN_CENTER_X GetScreenWidth()/2
#define SCREEN_CENTER_Y GetScreenHeight()/2
#define CLASSIC_XBOX_GREEN (Color){16, 124, 16, 255}
#define SLIME_GREEN (Color){0, 255, 0, 255}
#define DEFAULT_ERROR_CODE -1


#ifdef DT_LIMIT
#define DT_LIMIT_FIX dt > DT_LIMIT ? dt = DT_LIMIT : dt
#endif

// Must be 2 or 3.
#define GAME_D 3
#ifndef GAME_D
#define GAME_D 2
#endif
#if (GAME_D < 2) || (GAME_D > 3)
#define GAME_D 2
#endif

#define FUNCTIONAL FALSE

#define COMMON_MOVE_KEY_DOWN (IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D))

static inline signed int SIGN_OF(int x) { x = x<0 ? -1 : 1; return x; } 