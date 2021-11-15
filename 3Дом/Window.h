#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL2/SDL.h>
#include <memory>


class Window
{
public:
	using SDLWinPtr = std::shared_ptr<SDL_Window>;
	using GLContextPtr = std::shared_ptr<void>;
protected:
	int _width, _height;
	bool _fullscreen;

	SDLWinPtr _win;
	GLContextPtr _gl_context;
public:
	Window(int width, int height, bool fullscreen = false);
	virtual ~Window() = default;

	int width() const { return _width; }
	int height() const { return _height; }
	bool fullscreen() const { return _fullscreen; }

	void set_fullscreen(bool fs);
	void toggle_fullscreen();
	void resize(int w, int h);

	void main_loop();
	virtual void handle_event(const SDL_Event& e);
	virtual void handle_keys(const Uint8* keys);
	virtual void do_something();
	virtual void render();

	virtual void setup_gl() {}
};

#endif
