#ifndef GAME_GVIEW_HPP
#define GAME_GVIEW_HPP

#include "view.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class gview: public view{
private:
	const float pixel = 10.f;
	int flimit;
	sf::RenderWindow window_;
	void refresh_stats(sf::Event event);
public:
	gview();
	virtual void draw();
	virtual void mainloop();
	virtual void drawEmpty(coord pos);
	virtual void drawRabbit(coord rab);
	virtual void drawSnake(const Snake& snake);
	virtual void drawSnakeHead(coord head, Color clr, unsigned char symbol);
	virtual void drawSnakeMove(const Snake& snake);
	virtual void cleanSnake(const Snake& snake);
	virtual void stop();
	virtual int max_x();
	virtual int max_y();
	virtual int min_x();
	virtual int min_y();
	virtual void lvlup();
};

#endif //GAME_GVIEW_HPP