#ifndef GAME_TVIEW_HPP
#define GAME_TVIEW_HPP

#include "view.hpp"
#include <signal.h>

class tview: public view{
	public:
		tview();
		~tview();
		virtual void draw();
		virtual void mainloop();
	private:
		void clear();
		void putc(char c);
		void puts(const char* s);
		void setcolor(int color);
		void gline(int x, int y);
		void hline(int x, int y);
		void gotoxy(int x, int y);
		void box();
};

#endif //GAME_TVIEW_HPP