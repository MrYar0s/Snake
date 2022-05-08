#ifndef GAME_TVIEW_HPP
#define GAME_TVIEW_HPP

#include "view.hpp"

class tview: public view{
public:
	tview();
	~tview();
	void drawEmpty(coord pos);
	virtual void draw();
	virtual void drawRabbit(coord rab);
	virtual void drawSnake(const Snake& snake);
	virtual void drawSnakeHead(coord head, Color clr, unsigned char symbol);
	virtual void drawSnakeMove(const Snake& snake);
	virtual void stop();
	virtual void mainloop();
	virtual int max_x();
	virtual int max_y();
	virtual int min_x();
	virtual int min_y();
private:
	void clear();
	void putc(char c);
	void puts(const char* s);
	void setcolor(Color fore, Color back) const;
	void resetColor () const;
	void vline(int len);
	void hline(int len);
	void gotoxy(int x, int y);
	void gotoxyrel(int x, int y);
	void box(int width, int height);
	void refresh_stats();
	Game* game_;
};

#endif //GAME_TVIEW_HPP