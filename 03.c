// TASK:
// Draw a rectangle of width = 100 and height = 100 anywhere within the screens view
//
// New Functions needed from raylib:
// - draw_rectangle_rec
//
// New classes needed from raylib:
// - Rectangle

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