#include "human.hpp"
#include <cctype>

Human::Human(Game& game) : snake_(game.make_snake(4)) {}

void Human::Control(int key)
{
	auto old_dir = snake_.dir_;
	Direction new_dir = NOP;
	switch(std::toupper(key))
	{
		case 'W': 
				new_dir = UP;
				break;
		case 'D': 
				new_dir = RIGHT;
				break;
		case 'A': 
				new_dir = LEFT;
				break;
		case 'S': 
				new_dir = DOWN;
				break;
	}
	if(std::abs(new_dir - old_dir) == 1)
	{
		new_dir = old_dir;
	}
	else
	{
		snake_.dir_ = new_dir;
	}
}