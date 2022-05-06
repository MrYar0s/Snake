#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP
#include <utility>
#include <functional>
#include <list>

using coord = typename std::pair<int, int>;

enum Color
{
	BLACK = 0,
	RED = 1,
	GREEN = 2,
	YELLOW = 3,
	BLUE = 4,
	MAGENTA = 5,
	CYAN = 6,
	WHITE = 7,
	DEFAULT = 9
};

using KeyFn = std::function<void(int)>;

class view{
public:
	virtual ~view() {};
	static view* get(char const* type);
	virtual void draw() = 0;
	virtual void mainloop() = 0;
	int max_x();
	int max_y();
	void bindkey(std::function<void(int)> callkey);
private:
	static view* obj;
protected:
	std::list<KeyFn> callkey_;
	int width;
	int height;
};

#endif //GAME_VIEW_HPP