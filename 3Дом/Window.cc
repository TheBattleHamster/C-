
#include "Window.h"
#include "globals.h"
#include <stdexcept>

Window::Window(int width, int height, bool fullscreen)
: _width(width), _height(height), _fullscreen(fullscreen)
{
	Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

	if (_fullscreen) flags |= SDL_WINDOW_FULLSCREEN;

	_win = SDLWinPtr(
			SDL_CreateWindow(
					"SDL Window",
					SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					_width, _height,
					flags),
			SDL_DestroyWindow);
	if (_win == nullptr)
		SDL_DIE("SDL_CreateWindow()");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	_gl_context = GLContextPtr(
			SDL_GL_CreateContext(_win.get()),
			SDL_GL_DeleteContext);
	if (_gl_context == nullptr)
		SDL_DIE("SDL_GL_CreateContext()");
}

void Window::set_fullscreen(bool fs)
{
	if (fs == _fullscreen) return;
	_fullscreen = fs;
	Uint32 flags = SDL_GetWindowFlags(_win.get());
	if (fs)
		flags |= SDL_WINDOW_FULLSCREEN;
	else
		flags &= ~SDL_WINDOW_FULLSCREEN;
	SDL_SetWindowFullscreen(_win.get(), flags);
}

void Window::toggle_fullscreen()
{
	set_fullscreen(!_fullscreen);
}
void Window::main_loop()
{
	SDL_Event event;
	auto keys = SDL_GetKeyboardState(nullptr);
	for(;;) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				return;
			handle_event(event);
		}
		handle_keys(keys);

		do_something();

		render();
		SDL_GL_SwapWindow(_win.get());
	}
}

void Window::handle_event(const SDL_Event& e)
{

}

void Window::handle_keys(const Uint8* keys)
{

}

void Window::do_something()
{

}

void Window::render()
{

}
