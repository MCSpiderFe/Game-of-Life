#include <SDL.h>
#include <windows.h>

#include "Common.h"

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;

void drawCell(u_int x, u_int y, u_int color)
{
	Uint8* pixel_ptr = (Uint8*)surface->pixels + (y * CELL_SIZE * SCREEN_WIDTH + x * CELL_SIZE) * 4;

	for (u_int i = 0; i < CELL_SIZE; i++) {
		for (u_int j = 0; j < CELL_SIZE; j++) {
			*(pixel_ptr + j * 4) = color;
			*(pixel_ptr + j * 4 + 1) = color;
			*(pixel_ptr + j * 4 + 2) = color;
		}
		pixel_ptr += SCREEN_WIDTH * 4;
	}
}

#include "CellMap.h"

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);

	SDL_Event e;

	CellMap map(CELLMAP_WIDTH, SCREEN_HEIGHT);
	map.init();

	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) quit = true;
		}

		map.nextGen();

		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}