// Prevents circular includes
#pragma once

#include <SDL/SDL.h>

class MainGame {
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	int _screenWidth;
	int _screenHeight;

public:
	MainGame();
	~MainGame();

	void run();

	void initSystems();
};
