#include "game.hpp"

int main(int argc, char const *argv[])
{
	Game game;
	if(argc == 1)
	{
		game.set_view(view::get("text"));
	}
	else
	{
		game.set_view(view::get(argv[1]));
	}

	game.start();
	return 0;
}