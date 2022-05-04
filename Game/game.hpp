#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP
#include <list>
#include <random>
#include "view.hpp"

const int WIDTH = 1920;
const int HEIGHT = 1080;

class Game
{
public:
	Game();
	~Game();
	coord& get_rabbit(size_t pos);
	void generate_rabbit();
	void set_view(view* v);
	void start();
private:
	std::list<coord> rabbits;
	view* view_;
};

#endif //GAME_GAME_HPP