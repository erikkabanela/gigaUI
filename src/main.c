/* 🗿 UI */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "raylib.h"

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define Rectangle Win32Rectangle
#define CloseWindow Win32_CloseWindow
#define ShowCursor   Win32_ShowCursor
#include "windows_helpers.h"
#undef Rectangle  
#undef CloseWindow
#undef ShowCursor

#endif // _WIN32

#include "cjson/cJSON.h"

#include "gigaui.h"

bool dark_mode = false;

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

void process_radiobuttons(giga_radiobutton* group[], bool* radiobuttons_state[], int clicked){
	for (int i = 0; i < 3; i++)
		if (giga_process_radiobutton(group[i])) clicked = i;

	if (clicked != -1) {
		for (int i = 0; i < 3; i++)
			*radiobuttons_state[i] = (i == clicked);  // clicked one true, others false
	}
}

void process_checkbox(giga_checkbox* group[], bool* checkbox_state[]){
	for(int i = 0; i < 2; i++){
		if(giga_process_checkbox(group[i]))
			*checkbox_state[i] = group[i]->active ? false : true;
	}
}

void json_write(const char* filename, const char* key[], const char* value[], const int size){
	cJSON* json = cJSON_CreateObject();

	for(int i = 0; i < size; i++){
		cJSON_AddStringToObject(json, key[i], value[i]);
	}

	char* json_str = cJSON_Print(json);

	FILE* file = fopen(filename, "w");
	if(file){
		fputs(json_str, file);
		fclose(file);
	}

	free(json_str);
	cJSON_Delete(json);
}

void json_read(const char* filename, giga_radiobutton* grb){
	char buf[255];
	int i = 0;

	FILE* file = fopen(filename, "r");

	while(!feof(file)){
		buf[i++] = fgetc(file);
	}

	cJSON* root = cJSON_Parse(buf);

	if(cJSON_IsObject(root)){
		cJSON* item = NULL;
		cJSON_ArrayForEach(item, root){
			if(cJSON_IsString(item) && strcmp(item->string, "x") == 0){
				grb->x = atoi(item->valuestring);
			}
			else if(cJSON_IsString(item) && strcmp(item->string, "y") == 0){
				grb->y = atoi(item->valuestring);
			}
		}
	}

	fclose(file);
	cJSON_Delete(root);
}

int main(void){
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);

	SetTargetFPS(60);

	const char* window_title = "GIGAUI 🗿";
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, window_title);

	#ifdef _WIN32
		dark_mode = IsWindowsDarkMode();
		HWND hwnd = (HWND)GetWindowHandle();
		EnableDarkTitleBar(hwnd);
	#endif
	
	Font my_font = LoadFontEx("../fonts/JetBrainsMono-Medium.ttf", 32, NULL, 0);

	giga_text gt = { "", 80, 400, 32, Fade(GetColor(GIGA_BLACK), 0.8f) };

	float button_roundness = 0.2f;
	giga_button gb = { "Moai", button_roundness, false, (Rectangle) { 225, 100, 200, 50 },
		               Fade(GetColor(GIGA_BLUE), 0.9f), Fade(GetColor(GIGA_GREEN), 0.9f) };

	giga_radiobutton grb = { "Ok", 100, 200, 12.0f, 2.0f, false, GetColor(GIGA_GREEN) };
	giga_radiobutton grb2 = { "Cancel", 100, 260, 12.0f, 2.0f, false, GetColor(GIGA_GREEN) };
	giga_radiobutton grb3 = { "Bob", 100, 320, 12.0f, 2.0f, false, GetColor(GIGA_GREEN) };

	giga_radiobutton* radiobutton_group[3] = { &grb, &grb2, &grb3 };
	bool* radiobuttons_state[3] = { &grb.active, &grb2.active, &grb3.active };
	int clicked = -1;

	Texture2D checkbox_image = LoadTexture("checkmark.png");

	float checkbox_roundness = 0.4f;
	giga_checkbox gcb = { "Infinite Ammo", checkbox_image, (Rectangle) { 750, 190, 31, 28 }, checkbox_roundness, false };
	giga_checkbox gcb2 = { "Infinite HP", checkbox_image, (Rectangle) { 750, 250, 31, 28 }, checkbox_roundness, false };

	giga_checkbox* checkbox_group[2] = { &gcb, &gcb2 };
	bool* checkbox_state[2] = { &gcb.active, &gcb2.active };

	giga_slider gs = { (Rectangle) { 450, 475, 100, 3 }, 10.0f, 255, 0, GetColor(GIGA_GREEN) };

	giga_toggleswitch gts = { "Moai", (Rectangle) { 150, 500, 80, 40 }, 0.9f, true };
	giga_toggleswitch gts2 = { "Dark Mode", (Rectangle) { 150, 550, 80, 40 }, 0.9f, dark_mode };

	bool is_moai_visible = true;
	Texture2D moai = LoadTexture("moai.png");
	Rectangle moai_src = { 0, 0, -moai.width, moai.height };

	// JSON 
	
	const char* filename = "cfg.json";

	const int size = 3;

	char grb_x[4];
	char grb_y[4];

	//itoa(grb.x, grb_x, 10);
	//itoa(grb.y, grb_y, 10);

	const char* keys[] = { "label", "x", "y" };
	const char* values[] = { grb.label, grb_x, grb_y };

	//json_write(filename, keys, values, size);

	json_read(filename, &grb);

	printf("\n%d %d\n", grb.x, grb.y);

	while(!WindowShouldClose()){
		int screen_width = GetScreenWidth();
		int screen_height = GetScreenHeight();

		// Move moais head

		if(giga_button_is_clicked(&gb))
			is_moai_visible = !is_moai_visible;

		if(is_moai_visible){
			if(gts.active)
				moai_src.width = -moai.width;
			else
				moai_src.width = moai.width;
		}

		if(gts2.active)
			dark_mode = true;
		else
			dark_mode = false;

		int x = ((float)screen_width / 2) - moai.width / 2;
		int y = ((float)screen_height / 2) - moai.height / 2;

		gb.rec.x = ((float)screen_width / 2) - gb.rec.width / 2;
		//gb.rec.y = ((float)screen_height / 2) - gb.rec.height / 2;
		gb.rec.y = ((float)screen_height - gb.rec.height) - gb.rec.height / 2;
		giga_process_button(&gb);

		process_radiobuttons(radiobutton_group, radiobuttons_state, clicked);

		process_checkbox(checkbox_group, checkbox_state);

		giga_process_toggleswitch(&gts);
		giga_process_toggleswitch(&gts2);

		double value_current = giga_process_slider(&gs);

		BeginDrawing();

		ClearBackground(dark_mode ? GetColor(GIGA_BLACK) : GetColor(GIGA_WHITE));

		if(is_moai_visible)
			DrawTextureRec(moai, moai_src, (Vector2) { (float)x, (float)y }, (Color) { 255, 255, 255, (int)value_current });

		printf("%d\n", (int)value_current);

		//giga_draw_text(&gt);

		giga_draw_button(&gb, &my_font);
		//giga_draw_button(&gb2, &my_font);

		for(int i = 0; i < 3; i++){
			giga_draw_radiobutton(radiobutton_group[i], &my_font);
			if(radiobutton_group[i]->active){
				if(strcmp(radiobutton_group[i]->label, "Bob") == 0){
					char temp_label[255];
					strcpy(temp_label, radiobutton_group[i]->label);
					strcpy(gt.str, strcat(temp_label, " Gigachad"));
				}
				else strcpy(gt.str, radiobutton_group[i]->label);
			}
			giga_draw_text(&gt, &my_font);
		}

		for(int i = 0; i < 2; i++){
			giga_draw_checkbox(checkbox_group[i], &my_font);
		}

		giga_draw_slider(&gs);

		giga_draw_toggleswitch(&gts, &my_font);
		giga_draw_toggleswitch(&gts2, &my_font);

		EndDrawing();
	}

	UnloadFont(my_font);

	UnloadTexture(checkbox_image);
	UnloadTexture(moai);

	CloseWindow();

	return 0;
}
