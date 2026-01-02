
// TASK:
// IT'S TIME FOR A SNAKE!
//
// 1. I provided a starting snake list
// 2. Make it so that when the snake head eats a food, the snake grows like the snake is supposed to



#include "./raylib/include/raylib.h"

#define window_size 500
#define max_grid_size 32
#define max_grid_cells (max_grid_size*max_grid_size)

// NOTE in regards to C...
//
//
// When programming in C, or any language in general, I and others, prefer to know the 
// max amount of data we can possibly be dealing with
// 
// In a python version i did, i didn't cap out the max size the grid or the snake can be
// Really, a user would be able to scale the size until their computer wouldn't be able to
// handle it.
//
// In the C version , i could do something similar where i'm always dynamically changing
// the size of the array as needed at any particular time.
// 
// I think a better thing to do is jsut specify what is the max size of data i would want
// and just work with that, since that will be the max amount of data i ever really need
//
// Games, as i understand them, dont really benefit from working with dynamic arbitrary
// sizes of memory. Games are easiest to predict how they will run when you "fix" sizes
// of things. It also gets rid of a whole domain of memory management issues you can run
// into. 
//
// A lot of people think coding in C means manually dynamic memory management, and all the
// issues that come with it. And it scares some people off.
//
// The thing is, in my opinion, _most_ of the manual memory / dynamic management you might
// see in C education are completely rooted in  theoretical problems, and not necesarilly relate to 
// an actual practical problem someone is faced with.
//
// "What if" we want to support arbitrary sizes
// "What if" our users throw large amounts of data
// "What if" we only want to be using the amount of memory necesarry at any given time.
//
// The thing is, you can just as easily ask:
// "What if" we know how much memory we are dealing with at any given time and we never 
// have to worry about it?
//
// And the thing with games is that you CAN determine systemn requirements
// that your game is expected to run under.
// So you can answer that question.
//
// And being able to do that elimiates an entire class of problems you just 
// never have to deal with


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
	Vector2 snake[max_grid_cells];
	snake[0] = (Vector2){0,0};
	snake[1] = (Vector2){1,0};
	snake[2] = (Vector2){2,0};
	snake[3] = (Vector2){3,0};
	snake[4] = (Vector2){4,0};
	snake[5] = (Vector2){5,0};
	snake[6] = (Vector2){6,0};
	snake[7] = (Vector2){7,0};


	int snake_len = 8;
	int snake_head_index = snake_len-1;

	bool should_show_grid = false;

	int grid_size = 10;

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
			for (int i = 0; i < snake_head_index; i += 1) {
				snake[i] = snake[i+1];
			}
			snake[snake_head_index].x += move_amount.x;
			snake[snake_head_index].y += move_amount.y;
		}


		bool did_player_eat_food = Vector2_equals(food, snake[snake_head_index]);
		if (did_player_eat_food) {
			food = random_cell(grid_size);
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