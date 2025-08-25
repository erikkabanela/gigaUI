#include "gigaui.h" 

bool giga_process_checkbox(giga_checkbox* gcb){
	float more_range = 3.0f;
	Rectangle more_range_rec = { gcb->rec.x, gcb->rec.y, gcb->rec.width + more_range, gcb->rec.width + more_range };
	bool hovered = CheckCollisionPointRec(GetMousePosition(), more_range_rec);
	bool clicked = hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
	return clicked;
}

void giga_draw_checkbox(giga_checkbox* gcb, Font* my_font){
	if(gcb->active)
		DrawTextureEx(gcb->image, (Vector2) { gcb->rec.x - 2, gcb->rec.y - 1 }, 0.0f, 0.07f, WHITE);
	else
		DrawRectangleRounded(gcb->rec, 0.25f, 15, dark_mode ? GetColor(GIGA_LIGHTBLACK) : GetColor(GIGA_LIGHTGRAY));
	DrawRectangleRoundedLinesEx(gcb->rec, 0.25f, 15, 2.0f, dark_mode ? BLACK : GetColor(GIGA_GRAY));
	Vector2 label_pos = { gcb->rec.x + gcb->rec.width + 5, gcb->rec.y };

	int text_offsetX = 40;
	int text_offsetY = my_font->baseSize / 2;

	giga_text gt = { .x = gcb->rec.x + text_offsetX, .y = gcb->rec.y, .fontsize = my_font->baseSize, .color = dark_mode ? WHITE : BLACK };

	strcpy(gt.str, gcb->label);

	giga_draw_text(&gt, my_font);	
}
