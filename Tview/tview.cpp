#include "tview.hpp"
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <poll.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <chrono>

static termios old;
static bool final = false;

void onsig(int sig)
{
	final = true;
}

tview::tview()
{
	std::cout << "TEXT VIEW STARTED"/*<< std::flush*/;
	tcgetattr(0, &old);
	termios start = old;
	cfmakeraw(&start);
	start.c_lflag |= ISIG;
	tcsetattr(0, TCSANOW, &start);
	signal(SIGINT, onsig);
}

tview::~tview()
{
	clear();
	tcsetattr(0, TCSANOW, &old);
}

void tview::clear()
{
	resetColor();
	std::cout << "\e[H\e[J"<< std::flush;
}

void tview::puts(const char* s)
{
	std::cout << s << std::flush;
}

void tview::putc(char c)
{
	std::cout << c << std::flush;
}

void tview::gotoxy(int x, int y)
{
	std::cout << "\e["<< y << ";" << x << "H"/*<< std::flush*/;
}

void tview::gotoxyrel(int x, int y)
{
	char xc, yc;
	if(x < 0)
	{
		xc = 'D';
		x = -x;
	}
	else {xc = 'C';}
	if(y < 0)
	{
		yc = 'A';
		y = -y;
	}
	else {yc = 'B';}
	if(x) {std::cout << "\e[" << x << xc/*<< std::flush*/;}
	if(y) {std::cout << "\e[" << y << yc/*<< std::flush*/;}
}

void tview::hline(int len)
{
	for(int i = 0; i < len; i++)
	{
		std::cout << '#';
	}
	std::cout << std::flush;
}

void tview::vline(int len)
{
	for(int i = 0; i < len; i++)
	{
		std::cout << '#';
		gotoxyrel(-1, 1);
	}
	std::cout << std::flush;
}

void tview::box(int width, int height)
{
	setcolor(BLACK, BLUE);
	gotoxy(0, 0);
	hline(width - 1);
	gotoxy(0, 0);
	vline(height);
	gotoxy(0, height);
	hline(width - 1);
	gotoxy(width - 1, 0);
	vline(height);
}

void tview::setcolor(Color fore, Color back) const
{
	std::cout << "\e[" << fore + 30 << ";" << back + 40 << "m"/*<< std::flush*/;
}

void tview::resetColor () const
{
	setcolor(DEFAULT, DEFAULT);
}

void tview::draw()
{
	clear();
	box(width, height);
	setcolor(GREEN, BLUE);
	gotoxy(width/2, 0);
	puts("SNAKE");
	std::cout << std::flush;
}

void tview::drawRabbit(coord rab)
{
	gotoxy(rab.first, rab.second);
	setcolor(BLACK, YELLOW);
	putc('o');
}

void tview::drawSnake(const Snake& snake)
{
	setcolor(GREEN, snake.clr_);
	auto body = snake.pos_;
	for(auto cord : body)
	{
		gotoxy(cord.first, cord.second);
		putc('@');
	}
}

void tview::stop()
{
	final = true;
}

void tview::mainloop()
{
	pollfd fds = {0, POLLIN};
	int n;
	int nexttime = period_;
	while(!final)
	{
		auto start = std::chrono::system_clock::now();
		refresh_stats();
		n = poll(&fds, 1, nexttime);
		if(n < 0)
		{
			return;
		}
		if(n > 0)
		{
			auto end = std::chrono::system_clock::now();
			unsigned char key = std::getchar();
			for(auto&& call : callkey_)
			{
				call(key);
			}
			auto cur = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
			nexttime = period_ - cur.count();
		}
		if(nexttime < 0 || n == 0)
		{
			draw();
			for(auto&& call : calltick_)
			{
				call();
				std::cout << std::flush;
			}
			nexttime = period_;
		}
	}
}

void tview::refresh_stats()
{
	struct winsize stats;
	ioctl(1, TIOCGWINSZ, &stats);
	width = stats.ws_col;
	height = stats.ws_row;
}