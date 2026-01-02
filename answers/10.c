
#include "./raylib/include/raylib.h"

#define window_size 500

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
	bool should_show_grid = false;

	int grid_size = 5;

	Vector2 player;
	player.x = 0;
	player.y = 0;

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

		if (IsKeyPressed(KEY_UP)) {
			player.y -= 1;
		}
		else if (IsKeyPressed(KEY_DOWN)) {
			player.y += 1;
		}
		else if (IsKeyPressed(KEY_LEFT)) {
			player.x -= 1;
		}
		else if (IsKeyPressed(KEY_RIGHT)) {
			player.x += 1;
		}

		if (IsKeyPressed(KEY_F1)) {
			should_show_grid = !should_show_grid;
		}

		bool did_player_eat_food = Vector2_equals(food, player);
		if (did_player_eat_food) {
			food = random_cell(grid_size);
		}

		BeginDrawing();
		ClearBackground(SKYBLUE);
		
		Rectangle player_draw_rectangle = vector2_to_grid_rectangle(player, window_size, grid_size);
		DrawRectangleRec(player_draw_rectangle, WHITE);

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