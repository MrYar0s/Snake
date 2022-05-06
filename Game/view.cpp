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

void view::bindkey(std::function<void(int)> callkey)
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