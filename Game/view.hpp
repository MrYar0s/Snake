#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP
#include <utility>
#include <functional>
#include <list>

enum Color
{
	BLACK = 0,
	RED = 1,
	GREEN = 2,
	YELLOW = 3,
	BLUE = 4,
	MAGENTA = 5,
	CYAN = 6,
	WHITE = 7,
	DEFAULT = 9
};

using TickFn = std::function<void()>;
using KeyFn = std::function<void(int)>;
class view;
#include "game.hpp"


class view{
public:
	virtual ~view() {};
	static view* get(char const* type);
	virtual void draw() = 0;
	virtual void mainloop() = 0;
	void bindtick(TickFn calltick, int period);
	void bindkey(KeyFn callkey);
	virtual void drawRabbit(coord rab) = 0;
	virtual void drawEmpty(coord pos) = 0;
	virtual void drawSnake(const Snake& snake) = 0;
	virtual void drawSnakeHead(coord head, Color clr, unsigned char symbol) = 0;
	virtual void drawSnakeMove(const Snake& snake) = 0;
	virtual void cleanSnake(const Snake& snake) = 0;
	virtual void stop() = 0;
	virtual int max_x() = 0;
	virtual int max_y() = 0;
	virtual int min_x() = 0;
	virtual int min_y() = 0;
private:
	static view* obj;
protected:
	std::list<TickFn> calltick_;
	std::list<KeyFn> callkey_;
	int period_;
	int width;
	int height;
};

#endif //GAME_VIEW_HPP