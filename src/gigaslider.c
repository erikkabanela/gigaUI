#include "gigaui.h"

static float circle_x = -1;
static double value_current = 0;
static bool dragging = false;

double slider_to_value(int x, int x_min, int x_max, double v_min, double v_max) {
    return v_min + ((double)(x - x_min) * (v_max - v_min)) / (double)(x_max - x_min);
}

int giga_process_slider(giga_slider* gs){
	float circle_centerY = gs->rec.y + gs->rec.height / 2;
	if(circle_x == -1)
		circle_x = gs->rec.x;

	float more_range = 30.0f;
	Rectangle rec_more_range = { gs->rec.x, gs->rec.y - (more_range - gs->rec.height), gs->rec.width, gs->rec.height + (more_range * 2) };
	Vector2 mouse = GetMousePosition();
	bool hovered = CheckCollisionPointRec(mouse, rec_more_range) || CheckCollisionPointCircle(mouse, (Vector2) { circle_x, circle_centerY }, gs->circle_radius);
	if(hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		dragging = true;

	if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		dragging = false;

	if (dragging) {
        if (mouse.x < rec_more_range.x)
			mouse.x = rec_more_range.x;

        if (mouse.x > rec_more_range.x + rec_more_range.width)
			mouse.x = rec_more_range.x + rec_more_range.width;

		circle_x = mouse.x;
    }

	value_current = slider_to_value((int)circle_x, rec_more_range.x, (rec_more_range.x + rec_more_range.width), (double)gs->value_min, (double)gs->value_max);
	return value_current;
}

void giga_draw_slider(giga_slider* gs){
	float roundness = 1.0f;
	float circle_centerY = gs->rec.y + gs->rec.height / 2;
	DrawRectangleRounded(gs->rec, roundness, 15, dark_mode ? GetColor(GIGA_LIGHTBLACK) : GetColor(GIGA_GRAY));
	DrawCircle(circle_x, circle_centerY, gs->circle_radius, gs->color);
	//printf("%.2f %.2f\n", circle_x, GetMousePosition().x);
}
