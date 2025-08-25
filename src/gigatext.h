#pragma once

#include "raylib.h"

typedef struct {
	char str[255];
	int x, y;
	int fontsize;
	Color color;
} giga_text;

void giga_draw_text(giga_text* gt, Font* my_font);
