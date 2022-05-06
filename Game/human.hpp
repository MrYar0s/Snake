#ifndef GAME_HUMAN_HPP
#define GAME_HUMAN_HPP

#include "view.hpp"
#include "game.hpp"

class Human
{
public:
	explicit Human(Game& game);
private:
	Snake& snake_;
	void Control(int key);
};
#endif //GAME_HUMAN_HPP