// TASK:
// Make a Rectangle with sides of size 50 (it's a square)
// Everytime you press up, left, right, or down
// the Rectangle will move one side distance in that direction

// HINT: You may need to move the rectangle in this code to a outer scope

#include "./raylib/include/raylib.h"

#define window_size 500

int main () {
	int rectangle_count_per_side = 5;
	float rectangle_size = 50;

	InitWindow(window_size, window_size, "Snake");

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(SKYBLUE);
		Rectangle rectangle = {0, 0, rectangle_size, rectangle_size};
		DrawRectangleRec(rectangle, PINK); 
		EndDrawing();
	}
}