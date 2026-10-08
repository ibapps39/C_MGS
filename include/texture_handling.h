#pragma once
#include "common.h"


Model load_model() {
    // Asset file paths inside resources/IQMTest/
    const char* texture_path = "resources/IQMTest/ElderJamPlayer.png";
    const char* model_path   = "resources/IQMTest/ElderJamPlayer.iqm";

    // 1. Load Texture and IQM Model
    Texture player_texture = LoadTexture(texture_path);
    Model player_model = LoadModel(model_path);
    // Bind texture directly to model material map 0 (Diffuse)
    player_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = player_texture;
    return player_model;
}