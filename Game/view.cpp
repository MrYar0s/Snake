#include "view.hpp"
#include "tview.hpp"
#include "gview.hpp"
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

void view::bindtick(TickFn calltick, int period)
{
	calltick_.push_back(calltick);
	period_ = period;
}

void view::bindkey(KeyFn callkey)
{
	callkey_.push_back(callkey);
}

int view::max_x()
{
	return width - 1;
}

int view::max_y()
{
	return height - 1;
}