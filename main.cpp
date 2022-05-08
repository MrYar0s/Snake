#include "game.hpp"
#include "human.hpp"
#include "bot.hpp"

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
	v->draw();
	Game game{v};
	Human hm(game);
	Bot bot(game);
	v->mainloop();
	return 0;
}