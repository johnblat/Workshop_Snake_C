// TASK:
// Make the background start as a random color
// Every time you click the Space bar, make it a different random color


// New raylib functions needed:
// - is_key_pressed
// - get_random_value

// New raylib enum/classes to know about
// - KeyboardKey

#include "./raylib/include/raylib.h"

#define window_size 500

int main () {
	InitWindow(window_size, window_size, "Snake");

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);
		EndDrawing();
	}
}