#include "./raylib/include/raylib.h"

#define window_size 500

int main () {
	int rectangle_count_per_side = 5;

	InitWindow(window_size, window_size, "Snake");

	while(!WindowShouldClose()) {
		if (IsKeyPressed(KEY_EQUAL)) {
			rectangle_count_per_side += 1;
		}

		if (IsKeyPressed(KEY_MINUS)) {
			rectangle_count_per_side -= 1;
			bool is_value_too_small = rectangle_count_per_side < 1;
			if (is_value_too_small) {
				rectangle_count_per_side = 1;
			}
		}

		BeginDrawing();
		ClearBackground(SKYBLUE);

		for (int row = 0; row < rectangle_count_per_side; row += 1) {
			for (int column = 0; column < rectangle_count_per_side; column += 1) {
				float rectangle_size = (float)window_size / rectangle_count_per_side;

				Rectangle rectangle = {
					column * rectangle_size, 
					row * rectangle_size, 
					rectangle_size, 
					rectangle_size
				};
				DrawRectangleLinesEx(rectangle, 2, PINK); 
			}
		}

		EndDrawing();
	}
}