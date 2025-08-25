#pragma once

#include <stdbool.h>

#include "raylib.h"

#include "gigacolors.h"

typedef struct {
    char* label;
    float roundness;
    bool hovered;
    Rectangle rec;
    Color color, default_color;
} giga_button;

void giga_draw_button(giga_button* gb, Font* my_font);
bool giga_process_button(giga_button* gb);
bool giga_button_is_clicked(giga_button* gb);
