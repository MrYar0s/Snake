#ifndef GAME_GVIEW_HPP
#define GAME_GVIEW_HPP

#include "view.hpp"

class gview: public view{
public:
	gview();
	virtual void draw();
	virtual void mainloop();
	virtual void drawRabbit(coord rab);
	virtual void drawSnake(const Snake& snake);
};

#endif //GAME_GVIEW_HPP