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
	Game();
	~Game();
	const auto& get_rabbit() const;
	view* get_view();
	void generate_rabbit();
	void set_view(view* v);
	void update();
	void bindtick(int period);
	bool isinborder(coord rabbit) const;
private:
	std::list<coord> rabbits_;
	view* view_;
};

#endif //GAME_GAME_HPP