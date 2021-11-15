#include "MyWindow.h"
#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <iostream>


int main(int, char**)
{
	try {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			SDL_DIE("SDL_Init()");

		MyWindow w;

		w.main_loop();
	} catch (const std::exception& e) {
		std::cerr << "Произошла ошибка:\n" << e.what() << std::endl;
		return 1;
	} catch (...) {
		std::cerr << "Произошла неизвестная ошибка." << std::endl;
		return 1;
	}

	return 0;
}
