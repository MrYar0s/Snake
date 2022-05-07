#include "game.hpp"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib_x(1, WIDTH);
std::uniform_int_distribution<> distrib_y(1, HEIGHT);

Game::Game()
{}

void Game::bindtick(int period)
{
	view_->bindtick(std::bind(&Game::update, this), period);
}

Snake::Snake(std::list<coord>&& pos, Direction dir) : dir_(dir), pos_(pos) {}

std::list<coord> Snake::get_coords() const
{
	return pos_;
}

Snake& Game::make_snake(size_t len)
{
	std::list<coord> body;
	body.push_back(std::make_pair(10, 30));
	Direction dir = RIGHT;
	for(size_t i = 0; i < len; i++)
	{
		body.push_back(body.back());
	}
	snakes_.push_back(Snake(std::move(body), dir));
	return snakes_.back();
}

void Game::set_view(view* v)
{
	view_ = v;
}

bool Game::isinborder(coord rabbit) const
{
	if(rabbit.first <= 1 || rabbit.first >= (view_->max_x()))
	{
		return false;
	}
	if(rabbit.second <= 1 || rabbit.second >= (view_->max_y()))
	{
		return false;
	}
	return true;
}

void Game::generate_rabbit()
{
	int width = view_->max_x();
	int height = view_->max_y();
	coord c;
	c.first = distrib_x(gen)%width;
	c.second = distrib_y(gen)%height;
	rabbits_.push_back(c);
}

const auto& Game::get_rabbit() const
{
	return rabbits_;
}

view* Game::get_view()
{
	return view_;
}

void Game::update()
{
	while(rabbits_.size() <= START_RABBIT_AMOUNT)
	{
		generate_rabbit();
	}
	rabbits_.remove_if([=](auto rabbit){return !isinborder(rabbit);});
	for(auto rabbit_it : rabbits_)
	{
		view_->drawRabbit(rabbit_it);
	}
	for(auto snake_it : snakes_)
	{
		view_->drawSnake(snake_it);
	}
}

Game::~Game()
{
	delete view_;
}