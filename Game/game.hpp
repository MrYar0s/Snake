#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP
#include <list>
#include <random>

const int PERIOD = 300;

enum Direction
{
	UP = 0,
	DOWN = 1,
	LEFT = 3,
	RIGHT = 4,
	NOP = 9
};
using coord = typename std::pair<int, int>;
class Snake;
class Game;
#include "view.hpp"

const int WIDTH = 1920;
const int HEIGHT = 1080;
const int START_RABBIT_AMOUNT = 20;

class Snake
{
public:
	explicit Snake(std::list<coord>&& pos);
	bool is_alive = true;
	Color clr_ = MAGENTA;
	Direction dir_ = RIGHT;
	std::list<coord> pos_;
	unsigned char symbol_ = '>';
};

class Game
{
public:
	explicit Game(view* v);
	~Game();
	const auto& get_rabbit() const;
	view* get_view();
	Snake& make_snake(size_t len);
	void generate_rabbit();
	void update();
	bool isinborder(coord rabbit) const;
private:
	std::list<Snake> snakes_;
	std::list<coord> rabbits_;
	view* view_;
};

#endif //GAME_GAME_HPP