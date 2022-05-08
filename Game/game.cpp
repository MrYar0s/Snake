#include "game.hpp"
#include <algorithm>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib_x(1, WIDTH);
std::uniform_int_distribution<> distrib_y(1, HEIGHT);

coord nextcoord(coord pos, Direction dir)
{
	switch(dir)
	{
		case UP:
			--pos.second;
			break;
		case DOWN:
			++pos.second;
			break;
		case RIGHT:
			++pos.first;
			break;
		case LEFT:
			--pos.first;
			break;
		case NOP:
			break;
		default:
			break;
	}
	return pos;
}

Game::Game(view* v) : view_(v)
{
	view_->bindtick(std::bind(&Game::update, this), PERIOD);
	view_->bindkey([=](int key){if(std::toupper(key) == 'Q') view_->stop();});
}

Snake& Game::make_snake(size_t len)
{
	std::list<coord> body;
	body.push_back(std::make_pair(10, 20));
	for(size_t i = 0; i < len; i++)
	{
		body.push_back(body.back());
	}
	snakes_.push_back(Snake(std::move(body)));
	return snakes_.back();
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

const auto& Game::get_snakes() const
{
	return snakes_;
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
	for(auto&& snake_it : snakes_)
	{
		if(!snake_it.is_alive)
		{
			continue;
		}
		auto next = nextcoord(snake_it.pos_.front(), snake_it.dir_);
		auto predict = [=](auto&& snk){
			auto& l = snk.pos_;
			return std::find(l.cbegin(), l.cend(), next) != l.cend();
		};
		if((next.first <= view_->min_x() && snake_it.dir_ == LEFT) || (next.first >= view_->max_x() && snake_it.dir_ == RIGHT) ||
			(next.second <= view_->min_y() && snake_it.dir_ == UP) || (next.second > view_->max_y() && snake_it.dir_ == DOWN) ||
			std::find_if(snakes_.cbegin(), snakes_.cend(), predict) != snakes_.cend())
		{
			snake_it.is_alive = false;
			view_->cleanSnake(snake_it);
		}
		else
		{
			auto rabbit_it = std::find(rabbits_.begin(), rabbits_.end(), next);
			if(rabbit_it != rabbits_.end())
			{
				snake_it.pos_.emplace_front(next);
				view_->drawSnakeHead(snake_it.pos_.front(), snake_it.clr_, snake_it.symbol_);
				rabbits_.erase(rabbit_it);
			}
			else
			{
				snake_it.pos_.emplace_front(next);
				view_->drawSnakeMove(snake_it);
				snake_it.pos_.pop_back();
			}
		}
	}
}

Game::~Game()
{
	delete view_;
}