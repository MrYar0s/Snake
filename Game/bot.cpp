#include "bot.hpp"
#include <functional>

Bot::Bot(Game& game) : snake_(game.make_snake(10)), game_(game), rabbits_(game.get_rabbit()), snakes_(game.get_snakes())
{
	game.get_view()->bindtick(std::bind(&Bot::Control, this), 0);
}

void Bot::Control()
{
	auto head = snake_.pos_.front();
	auto rabbit = rabbits_.front();
	if(head.first < rabbit.first)
	{
		snake_.dir_ = RIGHT;
	}
	if(head.first > rabbit.first)
	{
		snake_.dir_ = LEFT;
	}
	if(head.second < rabbit.second)
	{
		snake_.dir_ = DOWN;
	}
	if(head.second > rabbit.second)
	{
		snake_.dir_ = UP;
	}
}