#include "view.hpp"
#include "tview.hpp"
#include "gview.hpp"
#include <sys/ioctl.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

view* view::obj = nullptr;

view* view::get(const char* type)
{
	if(obj == nullptr)
	{
		if (!strcmp(type, "text"))
		{
			obj = new tview;
		}
		else if(!strcmp(type, "graph")) 
		{
			obj = new gview;
		}
		else
		{
			printf("No such view\n");
		}
	}
	return obj;
}

void view::refresh_stats()
{
	struct winsize stats;
	ioctl(1, TIOCGWINSZ, &stats);
	width = stats.ws_col;
	height = stats.ws_row;
}

int view::max_x()
{
	return width - 1;
}

int view::max_y()
{
	return height - 1;
}