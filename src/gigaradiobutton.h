#pragma once

#include "raylib.h"

#include "gigacolors.h"

typedef struct {
    char label[255];
    int x, y;
    float radius, line_thick;
    bool active;
    Color color;
} giga_radiobutton;

bool giga_process_radiobutton(giga_radiobutton* grb);
void giga_draw_radiobutton(giga_radiobutton* grb, Font* my_font);
