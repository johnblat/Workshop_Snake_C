// TASK:
// Draw a series of rectangle lines in a grid, all evenly spaced.
// Make it so that when you press PLUS(EQUAL) OR MINUS(UNDERSCORE) , it adds the number of rectangles on 
// the sides of the grid

#include "./raylib/include/raylib.h"

#define window_size 500

int main () {
	int rectangle_count_per_side = 5;
	float rectangle_size = (float)window_size / rectangle_count_per_side;

	InitWindow(window_size, window_size, "Snake");

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(SKYBLUE);
		for (int row = 0; row < rectangle_count_per_side; row += 1) {
			for (int column = 0; column < rectangle_count_per_side; column += 1) {
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