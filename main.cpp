#include "game.hpp"
#include "human.hpp"

int main(int argc, char const *argv[])
{
	view* v;
	if(argc == 1)
	{
		v = view::get("text");
	}
	else
	{
		v = view::get(argv[1]);
	}
	Game game{v};
	Human hm(game);
	game.get_view()->mainloop();
	return 0;
}