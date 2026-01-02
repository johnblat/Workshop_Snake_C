#include "./raylib/include/raylib.h"

#define window_size 500


Color generate_random_color() {
	Color ret = {0,0,0,255};
	ret.r = GetRandomValue(0, 255);
	ret.g = GetRandomValue(0, 255);
	ret.b = GetRandomValue(0, 255);
	return ret;
}


int main () {

	Color background_color = generate_random_color();

	InitWindow(window_size, window_size, "Snake");

	while(!WindowShouldClose()) {
		bool should_randomize_background_color = IsKeyPressed(KEY_SPACE);
		if (should_randomize_background_color) {
			background_color = generate_random_color();
		}
		BeginDrawing();
		ClearBackground(background_color);
		EndDrawing();
	}
}