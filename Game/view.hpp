#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP
#include <utility>

using coord = typename std::pair<int, int>;

class view{
public:
	virtual ~view() {};
	static view* get(char const* type);
	virtual void draw() = 0;
	virtual void mainloop() = 0;
	void refresh_stats();
	int max_x();
	int max_y();
private:
	static view* obj;
protected:
	int width;
	int height;
};

#endif //GAME_VIEW_HPP