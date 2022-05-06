#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP
#include <list>
#include <random>
#include "view.hpp"

const int WIDTH = 1920;
const int HEIGHT = 1080;
const int START_RABBIT_AMOUNT = 20;

enum Direction
{
	UP = 0,
	DOWN = 1,
	LEFT = 3,
	RIGHT = 4,
	NOP = 9
};

class Game
{
public:
	explicit Game(size_t num);
	~Game();
	coord& get_rabbit(size_t pos);
	void generate_rabbit();
	void set_view(view* v);
	void start();
private:
	std::list<coord> rabbits_;
	view* view_;
};

#endif //GAME_GAME_HPP