#include "MainGame.h"

MainGame::MainGame() {
	// Reference nullptrs so we don't accidentally use a garbage pointer
	_window = nullptr;
	_renderer = nullptr;

	// Set the screen width and height
	_screenWidth = 1920;
	_screenHeight = 1080;
}

MainGame::~MainGame() {
	if (_renderer) {
		SDL_DestroyRenderer(_renderer);
		_renderer = nullptr;
	}

	if (_window) {
		SDL_DestroyWindow(_window);
		_window = nullptr;
	}

	SDL_Quit();
}

void MainGame::run() {
	initSystems();

}

void MainGame::initSystems() {
	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create a cenetered window and store the reference
	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		_screenWidth, _screenHeight, SDL_WINDOW_SHOWN);

	// Create a renderer for the window
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}
