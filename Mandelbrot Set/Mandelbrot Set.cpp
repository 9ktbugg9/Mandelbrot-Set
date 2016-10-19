#include "stdafx.h"
#include "Window.h"

#define FPS 30

double map(double value, double istart, double istop, double ostart, double ostop) {
	return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

int main(int args, char* argc[]) {
	Window window("Mandelbrot Set");
	Uint32 startingTick;
	bool running = true, done = false;

	while (running) {
		startingTick = SDL_GetTicks();
		if (!window.pEvents()) running = false;

		if (!done) {
			SDL_RenderClear(window._renderer);
			double w = 5;
			double h = (w * window.getHeight()) / window.getWidth();
			int maxIterations = 250;

			double xmin = -w / 2; //0.278587;
			double ymin = -h / 2; //-0.007440;
			double xmax = xmin + w; //0.285413;
			double ymax = ymin + h; //-0.012560;

			double ix = (xmax - xmin) / (window.getWidth());
			double iy = (ymax - ymin) / (window.getHeight());

			double y = ymin;
			for (int j = 0; j < window.getHeight(); j++) {
				double x = xmin;
				for (int i = 0; i < window.getWidth(); i++) {

					double a = x, b = y;
					int n = 0;
					while (n < maxIterations) {
						double aa = a * a, bb = b * b, twoab = 2.0 * a * b;
						a = aa - bb + x;
						b = twoab + y;
						if (aa*aa + bb*bb > 16.0) break;
						
						n++;
					}

					double color;
					if (n == maxIterations) color = 0;
					else {
						color = map(n, 0, 100, 0, 255);
						SDL_SetRenderDrawColor(window._renderer, color, color, color, 0xff);
						SDL_RenderDrawPoint(window._renderer, i, j);
					}
					x += ix;
				}
				y += iy;
				SDL_RenderPresent(window._renderer);
			}
			done = true;
		}

		if ((1000 / FPS) > SDL_GetTicks() - startingTick)
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - startingTick));
	}
	return 0;
}

