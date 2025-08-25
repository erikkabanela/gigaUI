#pragma once

#include "raylib.h"

#include "gigacolors.h"

typedef struct {
	char label[255];
	Texture2D image;
	Rectangle rec;
	float roundness;
	bool active;
} giga_checkbox;

bool giga_process_checkbox(giga_checkbox* gcb);

void giga_draw_checkbox(giga_checkbox* gcb, Font* my_font);
