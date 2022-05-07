#include "human.hpp"
#include <cctype>

Human::Human(Game& game) : snake_(game.make_snake(5))
{
	game.get_view()->bindkey(std::bind(&Human::Control, this, std::placeholders::_1));
}

void Human::Control(int key)
{
	auto old_dir = snake_.dir_;
	unsigned char symbol;
	Direction new_dir = NOP;
	switch(std::toupper(key))
	{
		case 'W': 
				new_dir = UP;
				symbol = '^';
				break;
		case 'D': 
				new_dir = RIGHT;
				symbol = '>';
				break;
		case 'A': 
				new_dir = LEFT;
				symbol = '<';
				break;
		case 'S': 
				new_dir = DOWN;
				symbol = 'v';
				break;
	}
	if(std::abs(new_dir - old_dir) == 1 || new_dir == NOP)
	{
		new_dir = old_dir;
	}
	else
	{
		snake_.dir_ = new_dir;
		snake_.symbol_ = symbol;
	}
}