// TASK:
//
// 1. Add a main menu that can be toggled to with ENTER
// 2. When entering the game (leaving the main menu), the snake should reset to some default state



#include "./raylib/include/raylib.h"

#define window_size 500
#define max_grid_size 32
#define max_grid_cells (max_grid_size*max_grid_size)

typedef enum {
	LEFT, RIGHT, UP, DOWN
} Direction;


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
	int grid_size = 10;
	Vector2 snake[max_grid_cells];
	snake[0] = random_cell(grid_size);
	int snake_head_index = 0;

	float wait_duration = 0.1;
	float wait_timer = wait_duration;

	Direction snake_direction = RIGHT;
	Direction next_snake_direction = snake_direction;

	bool should_show_grid = false;
	bool should_check_for_game_over = true;
	bool should_move_automatically = true;

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

		if (IsKeyPressed(KEY_F2)) {
			should_check_for_game_over = !should_check_for_game_over;
		}

		if (IsKeyPressed(KEY_F3)) {
			should_move_automatically = !should_move_automatically;
		}

		Vector2 move_amount = {0,0};

		if (should_move_automatically) {
			if (IsKeyPressed(KEY_UP)) {
				next_snake_direction = UP;
			}
			else if (IsKeyPressed(KEY_DOWN)) {
				next_snake_direction = DOWN;
			}
			else if (IsKeyPressed(KEY_LEFT)) {
				next_snake_direction = LEFT;				
			}
			else if (IsKeyPressed(KEY_RIGHT)) {
				next_snake_direction = RIGHT;								
			}
			
			float frame_time = GetFrameTime();
			wait_timer -= frame_time;

			bool just_finished_waiting = wait_timer <= 0;
			if (just_finished_waiting) {
				wait_timer = wait_duration;
				snake_direction = next_snake_direction;

				if (snake_direction == UP) {
					move_amount.y -= 1;
				}
				else if (snake_direction == DOWN) {
					move_amount.y += 1;					
				}
				else if (snake_direction == LEFT) {
					move_amount.x -= 1;					
				}
				else if (snake_direction == RIGHT) {
					move_amount.x += 1;					
				}
			}
		} else {
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


		if (should_check_for_game_over) {
			Vector2 head_cell = snake[snake_head_index];

			bool did_snake_collide_with_tail = false;
			for (int i = 0; i < snake_head_index; i++) {
				Vector2 tail_cell = snake[i];
				did_snake_collide_with_tail |= Vector2_equals(tail_cell, head_cell);
			}

			bool is_head_too_far_left = head_cell.x < 0;
			bool is_head_too_far_right = head_cell.x >= grid_size;
			bool is_head_too_far_up = head_cell.y < 0;
			bool is_head_too_far_down = head_cell.y >= grid_size;

			if (is_head_too_far_left) {
				snake_head_index = 0;
				snake[snake_head_index].x += 1;
				snake_direction = RIGHT;
				next_snake_direction = RIGHT;
			} else if (is_head_too_far_right) {
				snake_head_index = 0;
				snake[snake_head_index].x -= 1;
				snake_direction = LEFT;
				next_snake_direction = LEFT;
			} else if (is_head_too_far_up) {
				snake_head_index = 0;
				snake[snake_head_index].y += 1;
				snake_direction = DOWN;
				next_snake_direction = DOWN;
			} else if (is_head_too_far_down) {
				snake_head_index = 0;
				snake[snake_head_index].y -= 1;
				snake_direction = UP;
				next_snake_direction = UP;
			} else if (did_snake_collide_with_tail) {
				snake[0] = snake[snake_head_index];
				snake_head_index = 0;
			}
		}

		
		BeginDrawing();
		ClearBackground(SKYBLUE);

		for (int i = 0; i < snake_head_index; i += 1) {
			Vector2 snake_cell = snake[i];
			Rectangle rectangle =  vector2_to_grid_rectangle(snake_cell, window_size, grid_size);
			DrawRectangleRec(rectangle, LIGHTGRAY);
		}

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

		if (!should_check_for_game_over) {
			DrawText("Can't Die", 10, 10, 40, YELLOW);
		}

		if (!should_move_automatically) {
			DrawText("Manual Movement", 10, 60, 40, YELLOW);
		}

		EndDrawing();
		
	}
}