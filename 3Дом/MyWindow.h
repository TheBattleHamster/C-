
#ifndef MYWINDOW_H_
#define MYWINDOW_H_

#include "Window.h"
class MyWindow: public Window
{
public:
	MyWindow(): Window(800, 650) { setup_gl(); }
	MyWindow(const MyWindow&) = delete;
	virtual ~MyWindow() = default;

	virtual void render();
	virtual void setup_gl();
};




#endif /* MYWINDOW_H_ */
