#include "gigaui.h"

bool giga_process_toggleswitch(giga_toggleswitch* gts){
    bool hovered = CheckCollisionPointRec(GetMousePosition(), gts->rec); 
    if(hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        gts->active = !gts->active;
    
    return hovered;
}

void giga_draw_toggleswitch(giga_toggleswitch* gts, Font* my_font){
    Color bg_color;
    if(gts->active)
        bg_color = GetColor(GIGA_GREEN);
    else
        bg_color = GetColor(dark_mode ? GIGA_LIGHTBLACK : GIGA_GRAY);

    int padding = 4;
    int text_offsetX = 10;

    float knob_radius = gts->rec.height / 3;

    int knobX = gts->active ? (gts->rec.x + gts->rec.width - knob_radius - padding) : (gts->rec.x + knob_radius + padding);
    int knobY = gts->rec.y + gts->rec.height / 2;

    DrawRectangleRounded(gts->rec, gts->roundness, 15, bg_color);
    DrawCircle(knobX, knobY, knob_radius, dark_mode ? GetColor(GIGA_WHITE) : GetColor(GIGA_WHITE));

    Vector2 font_size = MeasureTextEx(*my_font, gts->label, my_font->baseSize, 0.0f);

    DrawTextEx(*my_font, gts->label, (Vector2) { gts->rec.x - font_size.x - text_offsetX, gts->rec.y + gts->rec.height / 2 - font_size.y / 2 }, my_font->baseSize, 0.0f,
               dark_mode ? WHITE : BLACK);

    //giga_text gt = { gts->label, gts->rec.x - font_size.x, gts->rec.y / 2, my_font->baseSize, BLACK };
    //giga_draw_text(&gt, my_font);
}
