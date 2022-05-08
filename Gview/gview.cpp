#include "gview.hpp"
#include <stdio.h>
#include <unistd.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>

sf::Color toSf(Color clr)
{
	switch(clr)
	{
		default:
		case BLACK:
			return sf::Color::Black;
		case RED:
			return sf::Color::Red;
		case GREEN:
			return sf::Color::Green;
		case YELLOW:
			return sf::Color::Yellow;
		case BLUE:
			return sf::Color::Blue;
		case MAGENTA:
			return sf::Color::Magenta;
		case CYAN:
			return sf::Color::Cyan;
		case WHITE:
			return sf::Color::White;
	}
}

Color toSf(sf::Color clr)
{
	if(clr == sf::Color::Red)
			return RED;
	if(clr == sf::Color::Green)
			return GREEN;
	if(clr == sf::Color::Yellow)
			return YELLOW;
	if(clr == sf::Color::Blue)
			return BLUE;
	if(clr == sf::Color::Magenta)
			return MAGENTA;
	if(clr == sf::Color::Cyan)
			return CYAN;
	if(clr == sf::Color::White)
			return WHITE;
	return BLACK;
}

int fromSf(sf::Keyboard::Key code)
{
	return code + 'A';
}

gview::gview() : window_(sf::VideoMode(800, 600), "Snake")
{
	window_.setFramerateLimit(20);
}

void gview::draw()
{
	sf::Vector2u win = window_.getSize();
	width = win.x/pixel;
	height = win.y/pixel;
}

void gview::drawEmpty(coord pos)
{
	auto box{sf::RectangleShape{sf::Vector2f(pixel, pixel)}};
	box.setFillColor(sf::Color::Black);
	box.setPosition(pixel * pos.first, pixel * pos.second);
	window_.draw(box);
}

void gview::drawRabbit(coord rab)
{
	auto circle{sf::CircleShape{pixel/2}};
	circle.setFillColor(sf::Color::Yellow);
	circle.setPosition(pixel * rab.first, pixel * rab.second);
	window_.draw(circle);
}

void gview::drawSnake(const Snake& snake)
{
	auto body = snake.pos_;
	for(auto cord : body)
	{
		drawSnakeHead(cord, snake.clr_, snake.symbol_);
	}
}

void gview::stop()
{
	window_.close();
}

void gview::drawSnakeHead(coord head, Color clr, unsigned char symbol)
{
	auto circle{sf::CircleShape{pixel/2}};
	circle.setFillColor(toSf(clr));
	circle.setPosition(pixel * head.first, pixel * head.second);
	window_.draw(circle);
}

void gview::drawSnakeMove(const Snake& snake)
{
	drawSnakeHead(snake.pos_.front(), snake.clr_, snake.symbol_);
	drawEmpty(snake.pos_.back());
}

void gview::cleanSnake(const Snake& snake)
{
	auto body = snake.pos_;
	for(auto cord : body)
	{
		drawEmpty(cord);
	}
}

void gview::mainloop()
{
	while(window_.isOpen())
	{
		sf::Event event;
		while(window_.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::KeyPressed:
					for(auto&& call : callkey_)
					{
						call(fromSf(event.key.code));
					}
					break;
				case sf::Event::Resized:
					refresh_stats(event);
					window_.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
					break;
				case sf::Event::Closed:
					stop();
					break;
				default:
					break;
			}
		}
		for(auto&& call : calltick_)
		{
			call();
		}
		window_.display();
	}
}

void gview::refresh_stats(sf::Event event)
{
	width = event.size.width/pixel;
	height = event.size.height/pixel;
}

int gview::max_x()
{
	return width;
}

int gview::max_y()
{
	return height;
}

int gview::min_x()
{
	return 0;
}

int gview::min_y()
{
	return 0;
}