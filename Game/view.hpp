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
class view;
#include "game.hpp"


class view{
public:
	virtual ~view() {};
	static view* get(char const* type);
	virtual void draw() = 0;
	virtual void mainloop() = 0;
	int max_x();
	int max_y();
	void bindtick(TickFn calltick, int period);
	virtual void drawRabbit(coord rab) = 0;
	virtual void drawSnake(const Snake& snake) = 0;
private:
	static view* obj;
protected:
	std::list<TickFn> calltick_;
	int period_;
	int width;
	int height;
};

#endif //GAME_VIEW_HPP