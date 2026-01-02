
#include "./raylib/include/raylib.h"

#define window_size 500

int main () {
	InitWindow(window_size, window_size, "Snake");

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);

		float rectangle_width = 100;
		float rectangle_height = rectangle_width;
		
		Rectangle top_left_rect = {
			0, 
			0, 
			rectangle_width, 
			rectangle_height
		};
		Rectangle top_right_rect = {
			window_size-rectangle_width,
			0,
			rectangle_width,
			rectangle_height
		};
		Rectangle bottom_left_rect = {
			0,
			window_size-rectangle_height,
			rectangle_width,
			rectangle_height
		};
		Rectangle bottom_right_rect = {
			window_size-rectangle_width,
			window_size-rectangle_height,
			rectangle_width,
			rectangle_height
		};
		Rectangle center_rect = {
			(float)window_size/2 - rectangle_width/2,
			(float)window_size/2 - rectangle_height/2,
			rectangle_width, 
			rectangle_height
		};

		DrawRectangleRec(top_left_rect, PINK);
		DrawRectangleRec(top_right_rect, PINK);
		DrawRectangleRec(bottom_left_rect, PINK);
		DrawRectangleRec(bottom_right_rect, PINK);
		DrawRectangleRec(center_rect, PINK);


		EndDrawing();
	}
}