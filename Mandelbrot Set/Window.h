#pragma once
#include "SDL.h"
#include <iostream>


using namespace std;

class Window {
private:
	void close();
	bool init(string);
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
public:


	SDL_Window* _window = NULL;
	SDL_Renderer* _renderer = NULL;

	bool pEvents();

	int getWidth() { return SCREEN_WIDTH; }
	int getHeight() { return SCREEN_HEIGHT; }


	Window(string winName) { init(winName); }
	~Window() { close(); }
};

