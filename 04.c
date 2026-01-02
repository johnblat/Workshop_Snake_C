// TASK:
// Draw Five rectangles all with width = 100, height = 100
// 1. Upper Left
// 2. Upper Right
// 3. Bottom Left
// 4. Bottom Right
// 5. Screen Center


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