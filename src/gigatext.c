#include "gigaui.h"

void giga_draw_text(giga_text* gt, Font* my_font){
    DrawTextEx(*my_font, gt->str, (Vector2) { (float)gt->x, (float)gt->y }, gt->fontsize, 0, dark_mode ? WHITE : BLACK);
}
