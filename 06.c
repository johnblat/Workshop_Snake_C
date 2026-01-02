// TASK:
// Draw 5x5 evenly spaced Rectangles on a 500 x 500 pixel grid
// Rectangles can be any color other than background color

// New raylib functions needed:
// - draw_rectangle_lines_ex
// ^ will make it so that we can draw the outline of the rectangle without filling it

// New control flow needed:
// - for (int i = 0; i < end; i += 1)


#include "./raylib/include/raylib.h"

#define window_size 500

int main () {
	int rectangle_count_per_side = 5;
	float rectangle_size = (float)window_size / rectangle_count_per_side;

	InitWindow(window_size, window_size, "Snake");

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(SKYBLUE);
		EndDrawing();
	}
}