#include "gigaui.h" 

bool giga_process_radiobutton(giga_radiobutton* grb){
    float more_range = 5.0f;
    bool hovered = CheckCollisionPointCircle(GetMousePosition(), 
                   (Vector2) { (float)grb->x + grb->line_thick, (float)grb->y + grb->line_thick }, grb->radius + more_range);
    bool clicked = hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    return clicked;
}

void giga_draw_radiobutton(giga_radiobutton* grb, Font* my_font){
    if(grb->active){
        DrawCircle(grb->x, grb->y, grb->radius, dark_mode ? GetColor(GIGA_BLACK) : GetColor(GIGA_WHITE));
        float innerline_thick = 6.0f;
        DrawRing((Vector2) { (float)grb->x, (float)grb->y }, grb->radius - innerline_thick, grb->radius, 0.0f, 365.0f, 64, grb->color);
    }
    else {
        DrawCircle(grb->x, grb->y, grb->radius, dark_mode ? GetColor(GIGA_LIGHTBLACK) : GetColor(GIGA_LIGHTGRAY));
        DrawRing((Vector2) { (float)grb->x, (float)grb->y }, grb->radius - grb->line_thick, grb->radius, 0.0f, 365.0f, 64, dark_mode ? BLACK : GetColor(GIGA_GRAY));
    }

    int text_offsetX = 20;
    int text_offsetY = my_font->baseSize / 2;
    //giga_text gt = { grb->label, grb->x + text_offsetX, grb->y - text_offsetY, my_font->baseSize, GetColor(GIGA_BLACK) };
    giga_text gt = { .x = grb->x + text_offsetX, .y = grb->y - text_offsetY, .fontsize = my_font->baseSize, .color = dark_mode ? WHITE : BLACK };

    strcpy(gt.str, grb->label);

    giga_draw_text(&gt, my_font);
}
