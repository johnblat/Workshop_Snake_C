

#include "./raylib/include/raylib.h"

#define window_size 500
#define max_grid_size 32
#define max_grid_cells (max_grid_size*max_grid_size)


bool Vector2_equals(Vector2 a, Vector2 b) {
	return a.x == b.x && a.y == b.y;
}


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


Vector2 get_random_cell_not_on_snake(Vector2 *snake, int head_index, float grid_size)  {
	Vector2 remaining_cells [max_grid_cells];
	int remaining_cells_count = 0;

	for (int r = 0; r < grid_size; r += 1) {
		for (int c = 0; c < grid_size; c += 1) {
			Vector2 possible_cell = {c, r};
			bool is_cell_in_snake = false;

			for (int i = 0; i <= head_index; i += 1) {
				Vector2 snake_cell = snake[i];
				bool yes = Vector2_equals(possible_cell, snake_cell);
				is_cell_in_snake |= yes;
			}

			if (!is_cell_in_snake) {
				remaining_cells[remaining_cells_count] = possible_cell;
				remaining_cells_count += 1;
			}
		}
	}

	int random_index_into_remaining_cells_array = GetRandomValue(0, remaining_cells_count-1);
	Vector2 random_cell = remaining_cells[random_index_into_remaining_cells_array];
	
	return random_cell;
}

int main () {
	Vector2 snake[max_grid_cells];
	snake[0] = (Vector2){0,0};
	snake[1] = (Vector2){1,0};
	snake[2] = (Vector2){2,0};
	snake[3] = (Vector2){3,0};
	snake[4] = (Vector2){4,0};
	snake[5] = (Vector2){5,0};
	snake[6] = (Vector2){6,0};
	snake[7] = (Vector2){7,0};

	int snake_head_index = 7;

	bool should_show_grid = false;

	int grid_size = 5;

	Vector2 food = random_cell((float)grid_size);

	InitWindow(window_size, window_size, "Snake");

	while(!WindowShouldClose()) {
		if (IsKeyPressed(KEY_EQUAL)) {
			grid_size += 1;
			bool is_value_too_big = grid_size > max_grid_size;
			if (is_value_too_big) {
				grid_size = max_grid_size;
			}
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

		Vector2 move_amount = {0,0};

		if (IsKeyPressed(KEY_UP)) {
			move_amount.y -= 1;
		}
		else if (IsKeyPressed(KEY_DOWN)) {
			move_amount.y += 1;
		}
		else if (IsKeyPressed(KEY_LEFT)) {
			move_amount.x -= 1;
		}
		else if (IsKeyPressed(KEY_RIGHT)) {
			move_amount.x += 1;
		}


		bool did_snake_move = !Vector2_equals(move_amount, (Vector2){0,0});
		if (did_snake_move) {
			Vector2 snake_head = snake[snake_head_index];

			Vector2 next_snake_head;
			next_snake_head.x = snake_head.x + move_amount.x;
			next_snake_head.y = snake_head.y + move_amount.y;

			bool will_snake_eat_food = Vector2_equals(next_snake_head, food);
			if (will_snake_eat_food) {
				snake_head_index += 1;
				int max_snake_size = grid_size*grid_size;
				bool did_just_win = snake_head_index == max_snake_size-1;
				if (did_just_win) {
					snake_head_index = 0;
				}
				snake[snake_head_index] = next_snake_head;
				food = get_random_cell_not_on_snake(snake, snake_head_index, grid_size);
			} else {
				for (int i = 0; i < snake_head_index; i += 1) {
					snake[i] = snake[i+1];
				}
				snake[snake_head_index] = next_snake_head;
			}
		}


		
		BeginDrawing();
		ClearBackground(SKYBLUE);

		Rectangle snake_head_rectangle = vector2_to_grid_rectangle(snake[snake_head_index], window_size, grid_size);
		DrawRectangleRec(snake_head_rectangle, WHITE);

		for (int i = 0; i < snake_head_index; i += 1) {
			Vector2 snake_cell = snake[i];
			Rectangle rectangle =  vector2_to_grid_rectangle(snake_cell, window_size, grid_size);
			DrawRectangleRec(rectangle, LIGHTGRAY);
		}

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