#include "gview.hpp"
#include <stdio.h>
#include <unistd.h>

gview::gview()
{
	printf("GRAPHIC\n");
}

void gview::draw()
{
	static int i = 0;
	printf("GRAPHICS: %d\n", i);
	i++;
}

void gview::drawRabbit(coord rab) {}

void gview::drawSnake(const Snake& snake) {}

void gview::mainloop()
{
	while(1)
	{
		draw();
		usleep(500);
	}
}