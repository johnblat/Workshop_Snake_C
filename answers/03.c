#include "./raylib/include/raylib.h"

#define window_size 500

int main () {
	InitWindow(window_size, window_size, "Snake");

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);
		Rectangle rectangle = {25, 25, 100, 100};
		DrawRectangleRec(rectangle, PINK);
		EndDrawing();
	}
}