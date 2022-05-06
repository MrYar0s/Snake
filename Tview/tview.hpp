#ifndef GAME_TVIEW_HPP
#define GAME_TVIEW_HPP

#include "view.hpp"

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
		void vline(int len);
		void hline(int len);
		void gotoxy(int x, int y);
		void gotoxyrel(int x, int y);
		void box(int width, int height);
};

#endif //GAME_TVIEW_HPP