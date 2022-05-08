#include "model.hpp"

Snake::Snake(std::list<coord>&& pos, Color clr) : clr_(clr), pos_(pos) {}

Death::Death(Snake* snake) : snake_(snake)
{
	snake->is_alive = false;
}

void Death::die()
{
	snake_->pos_.clear();
}