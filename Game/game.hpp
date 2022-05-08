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
	const auto& get_rabbit() const;
	const auto& get_snakes() const;
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