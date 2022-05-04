#include "game.hpp"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib_x(1, WIDTH);
std::uniform_int_distribution<> distrib_y(1, HEIGHT);

Game::Game() {}

void Game::set_view(view* v)
{
	view_ = v;
}

void Game::generate_rabbit()
{
	coord c;
	c.first = distrib_x(gen);
	c.second = distrib_y(gen);
	rabbits.push_back(c);
}

void Game::start()
{
	view_->mainloop();
}

Game::~Game()
{
	delete view_;
}