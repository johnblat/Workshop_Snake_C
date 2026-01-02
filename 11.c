
// TASK:
// IT'S TIME FOR A SNAKE!
//
// 1. I provided a starting snake list
// 2. Draw the entire snake and make sure the head is a different color than the tail segments
// 3. When using the arrow keys to move, make it so that it moves like the snake is supposed to
// 4. When the snake's head touches a food, the food should get placed in a random spot like we were doing before


// NOTE: 
// 
// 1. Make the grid size default to something higher now. I made it 16.
// 2. Make it so that the begin_drawing and end_drawing functions are called only before and after the actual drawing code. 
//           Gameplay code will go above.


// Optional* New raylib functions to know about:
// - vector2_add
//
// *You can do this without the function, but its also possible to do it with the function



#include "./raylib/include/raylib.h"

#define window_size 500
#define max_grid_size 32
#define max_grid_cells (max_grid_size*max_grid_size)


Vector2 random_cell(int grid_size) {
	int max_val = grid_size - 1;
	Vector2 ret = {
		GetRandomValue(0, max_val),
		GetRandomValue(0, max_val)
	};
	return ret;
}


Rectangle vector2_to_grid_rectangle(Vector2 v, float screen_size, float grid_size) {
	float rectangle_draw_size = screen_size / grid_size;

	Rectangle ret;
	ret.x = v.x * rectangle_draw_size;
	ret.y = v.y * rectangle_draw_size;
	ret.width = rectangle_draw_size;
	ret.height = rectangle_draw_size;

	return ret;  
}


bool Vector2_equals(Vector2 a, Vector2 b) {
	return a.x == b.x && a.y == b.y;
}


int main () {
	Vector2 snake[8];
	int snake_len = 8;
	
	snake[0] = (Vector2){0,0};
	snake[1] = (Vector2){1,0};
	snake[2] = (Vector2){2,0};
	snake[3] = (Vector2){3,0};
	snake[4] = (Vector2){4,0};
	snake[5] = (Vector2){5,0};
	snake[6] = (Vector2){6,0};
	snake[7] = (Vector2){7,0};

	int snake_head_index = snake_len-1;

	bool should_show_grid = false;

	int grid_size = 10;

	Vector2 food = random_cell((float)grid_size);

	InitWindow(window_size, window_size, "Snake");

	while(!WindowShouldClose()) {
		if (IsKeyPressed(KEY_EQUAL)) {
			grid_size += 1;
		}
		else if (IsKeyPressed(KEY_MINUS)) {
			grid_size -= 1;
			bool is_value_too_small = grid_size < 1;
			if (is_value_too_small) {
				grid_size = 1;
			}
		}

		if (IsKeyPressed(KEY_F1)) {
			should_show_grid = !should_show_grid;
		}


		bool did_player_eat_food = Vector2_equals(food, snake[snake_head_index]);
		if (did_player_eat_food) {
			food = random_cell(grid_size);
		}

		BeginDrawing();
		ClearBackground(SKYBLUE);

		Rectangle snake_head_rectangle = vector2_to_grid_rectangle(snake[snake_head_index], window_size, grid_size);
		DrawRectangleRec(snake_head_rectangle, WHITE);

		Rectangle food_draw_rectangle = vector2_to_grid_rectangle(food, window_size, grid_size);
		DrawRectangleRec(food_draw_rectangle, PINK);

		if (should_show_grid) {
			for (int row = 0; row < grid_size; row += 1) {
				for (int column = 0; column < grid_size; column += 1) {
					Vector2 cell;
					cell.x = column;
					cell.y = row;
					Rectangle rectangle = vector2_to_grid_rectangle(cell, window_size, grid_size);
					DrawRectangleLinesEx(rectangle, 2, RED); 
				}
			}
		}
			

		EndDrawing();
	}
}