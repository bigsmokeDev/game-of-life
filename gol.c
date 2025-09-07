#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "raylib/raylib.h"

#define BOARD_COLS 100
#define BOARD_ROWS 100
#define CELL_SIZE 10

bool board[BOARD_COLS][BOARD_ROWS];

int get_nbors(int cx, int cy) {
	int nbors = 0;
	for (int col = cx - 1; col <= cx + 1; ++col) {
		for (int row = cy - 1; row <= cy + 1; ++row) {
			if (col < 0 || col >= BOARD_COLS || row < 0 || row >= BOARD_ROWS)
				continue;
			if (board[col][row] && !(col == cx && row == cy))
				nbors++;
		}
	}
	return nbors;
}

void update(void) {
	bool next_board[BOARD_COLS][BOARD_ROWS];

	for (int col = 0; col < BOARD_COLS; ++col) {
		for (int row = 0; row < BOARD_ROWS; ++row) {
			int nbors = get_nbors(col, row);
			if (board[col][row])
				next_board[col][row] = (nbors == 2 || nbors == 3);
			else 
				next_board[col][row] = (nbors == 3);
		}
	}

	memcpy(board, next_board, BOARD_COLS * BOARD_ROWS * sizeof(bool));
}

void draw(void) {
	for (int col = 0; col < BOARD_COLS; ++col) {
		for (int row = 0; row < BOARD_ROWS; ++row) {
			if (board[col][row])
				DrawRectangle(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);
		}
	}
}

int main(void) {
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(800, 600, "Conway's Game of Life");

	int ox = 30;
	int oy = 10;

	// block
	board[ox+1][oy+5] = true;
	board[ox+1][oy+6] = true;
	board[ox+2][oy+5] = true;
	board[ox+2][oy+6] = true;

	// left square
	board[ox+11][oy+5] = true;
	board[ox+11][oy+6] = true;
	board[ox+11][oy+7] = true;
	board[ox+12][oy+4] = true;
	board[ox+12][oy+8] = true;
	board[ox+13][oy+3] = true;
	board[ox+13][oy+9] = true;
	board[ox+14][oy+3] = true;
	board[ox+14][oy+9] = true;
	board[ox+15][oy+6] = true;
	board[ox+16][oy+4] = true;
	board[ox+16][oy+8] = true;
	board[ox+17][oy+5] = true;
	board[ox+17][oy+6] = true;
	board[ox+17][oy+7] = true;
	board[ox+18][oy+6] = true;

	// middle cluster
	board[ox+21][oy+3] = true;
	board[ox+21][oy+4] = true;
	board[ox+21][oy+5] = true;
	board[ox+22][oy+3] = true;
	board[ox+22][oy+4] = true;
	board[ox+22][oy+5] = true;
	board[ox+23][oy+2] = true;
	board[ox+23][oy+6] = true;

	// right cluster
	board[ox+25][oy+1] = true;
	board[ox+25][oy+2] = true;
	board[ox+25][oy+6] = true;
	board[ox+25][oy+7] = true;

	// far right block
	board[ox+35][oy+3] = true;
	board[ox+35][oy+4] = true;
	board[ox+36][oy+3] = true;
	board[ox+36][oy+4] = true;

	while (!WindowShouldClose()) {
		//if (IsKeyPressed(KEY_SPACE))
			update();

		BeginDrawing();
		ClearBackground((Color){20, 20, 20, 255});

		draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
