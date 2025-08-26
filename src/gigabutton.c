#include "gigaui.h"

void giga_draw_button(giga_button* gb, Font* my_font){
    Vector2 font_size = MeasureTextEx(*my_font, gb->label, my_font->baseSize, 0.0f);
    int font_offsetX = 10;
    int font_offsetY = 10;

    // Change font size with button size

    if(gb->rec.width < font_size.x && gb->rec.height < font_size.y){
        gb->rec.width = (int)font_size.x + font_offsetX;
        gb->rec.height = (int)font_size.y + font_offsetY;
    }

    DrawRectangleRounded(gb->rec, gb->roundness, 15, gb->color); // Always 15 segments ඞ
    DrawRectangleRoundedLinesEx(gb->rec, gb->roundness, 0, 1.5f, dark_mode ? BLACK : GetColor(GIGA_GRAY));
    Vector2 label_pos = { gb->rec.x + (gb->rec.width - font_size.x) / 2, gb->rec.y + (gb->rec.height - font_size.y) / 2 };
    DrawTextEx(*my_font, gb->label, label_pos, my_font->baseSize, 0.0f, dark_mode ? WHITE : BLACK); 
}

bool giga_button_is_clicked(giga_button* gb){
    if(!edit_mode && gb->hovered){
	    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    }
    return false;
}

bool giga_process_button(giga_button* gb){
    gb->hovered = CheckCollisionPointRec(GetMousePosition(), gb->rec);
    
    static bool dragging = false; 
    static Vector2 drag_offset = {0};

    if(edit_mode){
        if(!dragging && gb->hovered && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            dragging = true;
            drag_offset = (Vector2) { GetMousePosition().x - gb->rec.x, GetMousePosition().y - gb->rec.y };
        }
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            dragging = false;
        }

        if(dragging){
            gb->rec.x = GetMousePosition().x - drag_offset.x;
            gb->rec.y = GetMousePosition().y - drag_offset.y;
        }
    }
    else{
        Color hover_color = Fade(gb->default_color, (gb->default_color.a / 255) + 1.0f);
        if(giga_button_is_clicked(gb))
            gb->color = Fade(gb->default_color, 0.5f);
        else
            gb->color = gb->hovered ? hover_color : gb->default_color;
    }
    return gb->hovered;
}
