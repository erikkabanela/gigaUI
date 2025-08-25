#pragma once

#include "raylib.h"

#include "gigacolors.h"
#include "gigatext.h"

typedef struct {
    char label[255];
    Rectangle rec;
    float roundness;
    bool active;
} giga_toggleswitch;

bool giga_process_toggleswitch(giga_toggleswitch* gts);
void giga_draw_toggleswitch(giga_toggleswitch* gts, Font* my_font);
