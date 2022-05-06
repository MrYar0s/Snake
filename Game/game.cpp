#include "game.hpp"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib_x(1, WIDTH);
std::uniform_int_distribution<> distrib_y(1, HEIGHT);

Game::Game() {}

void Game::bindtick(int period)
{
	view_->bindtick(std::bind(&Game::update, this), period);
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
}

Game::~Game()
{
	delete view_;
}