#ifndef GAME_BOT_HPP
#define GAME_BOT_HPP

#include "view.hpp"
#include "game.hpp"

class Bot
{
public:
	Bot(Game& game);
private:
	Snake& snake_;
	Game& game_;
	const std::list<coord>& rabbits_;
	const std::list<Snake>& snakes_;
	void Control();
};

#endif //GAME_BOT_HPP