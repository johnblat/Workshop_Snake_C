#include "./raylib/include/raylib.h"

#define window_size 500

int main () {
	int rectangle_count_per_side = 5;
	float rectangle_size = 50;
	Rectangle rectangle = {0, 0, rectangle_size, rectangle_size};


	InitWindow(window_size, window_size, "Snake");

	while(!WindowShouldClose()) {
		if (IsKeyPressed(KEY_UP)) {
			rectangle.y -= rectangle_size;
		}
		else if (IsKeyPressed(KEY_DOWN)) {
			rectangle.y += rectangle_size;
		}
		else if (IsKeyPressed(KEY_LEFT)) {
			rectangle.x -= rectangle_size;
		}
		else if (IsKeyPressed(KEY_RIGHT)) {
			rectangle.x += rectangle_size;
		}

		BeginDrawing();
		ClearBackground(SKYBLUE);
		DrawRectangleRec(rectangle, PINK); 
		EndDrawing();
	}
}