#include "./raylib/include/raylib.h"

#define window_size 500

int main () {
	Rectangle player;
	player.x = 0;
	player.y = 0;
	player.width = 1;
	player.height = 1;

	int rectangle_count_per_side = 5;

	InitWindow(window_size, window_size, "Snake");

	while(!WindowShouldClose()) {
		if (IsKeyPressed(KEY_EQUAL)) {
			rectangle_count_per_side += 1;
		}
		else if (IsKeyPressed(KEY_MINUS)) {
			rectangle_count_per_side -= 1;
			bool is_value_too_small = rectangle_count_per_side < 1;
			if (is_value_too_small) {
				rectangle_count_per_side = 1;
			}
		}

		if (IsKeyPressed(KEY_UP)) {
			player.y -= 1;
		}
		else if (IsKeyPressed(KEY_DOWN)) {
			player.y += 1;
		}
		else if (IsKeyPressed(KEY_LEFT)) {
			player.x -= 1;
		}
		else if (IsKeyPressed(KEY_RIGHT)) {
			player.x += 1;
		}

		BeginDrawing();
		ClearBackground(SKYBLUE);

		float rectangle_draw_size = (float)window_size / rectangle_count_per_side;
		
		Rectangle player_draw_rectangle;
		player_draw_rectangle.x = player.x * rectangle_draw_size;
		player_draw_rectangle.y = player.y * rectangle_draw_size;
		player_draw_rectangle.width = player.width * rectangle_draw_size;
		player_draw_rectangle.height = player.height * rectangle_draw_size;

		DrawRectangleRec(player_draw_rectangle, WHITE);

		for (int row = 0; row < rectangle_count_per_side; row += 1) {
			for (int column = 0; column < rectangle_count_per_side; column += 1) {

				Rectangle rectangle = {
					column * rectangle_draw_size, 
					row * rectangle_draw_size, 
					rectangle_draw_size, 
					rectangle_draw_size
				};
				DrawRectangleLinesEx(rectangle, 2, RED); 
			}
		}

		EndDrawing();
	}
}