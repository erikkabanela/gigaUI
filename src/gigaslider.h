#pragma once

#include "raylib.h"

typedef struct {
    Rectangle rec;
    float circle_radius;
    int value_min, value_max;
    Color color;
} giga_slider;

int giga_process_slider(giga_slider* gs);
void giga_draw_slider(giga_slider* gs);
