#ifndef GAME_MODEL_HPP
#define GAME_MODEL_HPP

#include <list>
using coord = typename std::pair<int, int>;

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

enum Direction
{
	UP = 0,
	DOWN = 1,
	LEFT = 3,
	RIGHT = 4,
	NOP = 9
};

class Snake
{
public:
	explicit Snake(std::list<coord>&& pos, Color clr);
	bool is_alive = true;
	Color clr_ = MAGENTA;
	Direction dir_ = RIGHT;
	std::list<coord> pos_;
	unsigned char symbol_ = '>';
};

class Death
{
public:
	explicit Death(Snake* snake);
	void die();
private:
	Snake* snake_;
};

#endif //GAME_MODEL_HPP