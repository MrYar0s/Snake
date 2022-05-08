#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP
#include <random>
#include "model.hpp"
#include "view.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;
const int START_RABBIT_AMOUNT = 20;

class Game
{
public:
	explicit Game(view* v);
	~Game();
	const std::list<coord>& get_rabbit() const;
	const std::list<Snake>& get_snakes() const;
	view* get_view();
	Snake& make_snake(size_t len, Color clr);
	void generate_rabbit();
	void update();
	bool isinborder(coord rabbit) const;
	void lvlup();
private:
	std::list<Snake> snakes_;
	std::list<coord> rabbits_;
	std::list<Death> deaths_;
	view* view_;
};

#endif //GAME_GAME_HPP