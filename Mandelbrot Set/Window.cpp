#include "stdafx.h"
#include "Window.h"

bool Window::init(string WINDOW_NAME) {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		cout << "-Initialization Failed- Reason: " << SDL_GetError() << endl;
		success = false;
	}

	else {
		SCREEN_WIDTH = 640 * 2;
		SCREEN_HEIGHT = 480 * 2;
		_window = SDL_CreateWindow(WINDOW_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (_window == NULL) {
			cout << "-Window Creation Failed- Reason: " << SDL_GetError() << endl;
			success = false;
		}

		else {

			_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED );

			SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

			if (_renderer == NULL) {
				cout << "-Renderer Creation Failed- Reason: " << SDL_GetError() << endl;
				success = false;
			}
		}
	}
	return success;
}

bool Window::pEvents() {
	bool running = true;
	SDL_Event event;

	if (SDL_PollEvent(&event) != NULL) {
		switch (event.type) {
			case SDL_QUIT: running = false; break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) running = false;
				break;

			default: break;
		}
	}
	return running;
}

void Window::close() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	_window = NULL; _renderer = NULL;

	SDL_Quit();
}