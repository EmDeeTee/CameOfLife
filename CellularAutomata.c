#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#define SIZE 10
#define DRAW_DELAY_MS 100

int cells[SIZE][SIZE] = {0};
int generation_num = 0;

void draw(void) {
	printf("===== GENERATION %i =====\n", generation_num);
	for (size_t i = 0; i < SIZE; i++) {
		for (size_t ii = 0; ii < SIZE; ii++) {
			printf("%i, ", cells[ii][i]);
		}
		printf("\n");
	}
}

int get_alive_n_cells(int x, int y) {
	int n = 0;

	for (int row = -1; row <= 1; row++) {
		for (int col = -1; col <= 1; col++) {
			if (row == 0 && col == 0) continue;

			int newRow = row + y;
			int newCol = col + x;

			if (cells[newCol][newRow] == 1) {
				n++;
			}
		}
	}

	return n;
}

void next_generation(void) {
	int temp_cells[SIZE][SIZE] = { 0 };
	memcpy(temp_cells, cells, sizeof(cells));

	for (size_t i = 0; i < SIZE; i++) {
		for (size_t ii = 0; ii < SIZE; ii++) {
			if (cells[ii][i] == 1) {
				if (get_alive_n_cells(ii, i) < 2) {
					temp_cells[ii][i] = 0;
				}
				else if (get_alive_n_cells(ii, i) == 2 || get_alive_n_cells(ii, i) == 3) {
					temp_cells[ii][i] = 1;
				}
				else if (get_alive_n_cells(ii, i) > 3) {
					temp_cells[ii][i] = 0;
				}
			}
			else if (cells[ii][i] == 0 && get_alive_n_cells(ii, i) == 3) {
				temp_cells[ii][i] = 1;
			}
		}
	}

	memcpy(cells, temp_cells, sizeof(cells));

	generation_num++;
}

void loop() {
	while (1 == 1) {
		draw();
		Sleep(DRAW_DELAY_MS);
		system("cls"); // I know, I know... Don't tell me
		next_generation();
	}
}

int main(void) {
	// Glider
	cells[1][0] = 1;
	cells[2][1] = 1;
	cells[0][2] = 1;
	cells[1][2] = 1;
	cells[2][2] = 1;
	loop();
}