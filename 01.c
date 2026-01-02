// TASK:
// Make the background in the window a different color than black
// New Functions needed from raylib:
// - ClearBackground()
// New struct needed from raylib:
// - Color

#include "./raylib/include/raylib.h"

#define window_size 500

int main () {
	InitWindow(window_size, window_size, "Snake");

	while(!WindowShouldClose()) {
		BeginDrawing();
		EndDrawing();
	}
}