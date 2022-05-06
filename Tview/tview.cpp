#include "tview.hpp"
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <poll.h>
#include <signal.h>
#include <sys/ioctl.h>

termios old;
bool final = false;

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
}


void on_key(char key)
{
	if(key == 'q')
	{
		final = true;
	}
}

void tview::mainloop()
{
	refresh_stats();
	pollfd fds = {0, POLLIN};
	int n;
	while(!final)
	{
		draw();
		n = poll(&fds, 1, 500);
		if(n == 1)
		{
			unsigned char letter = getchar();
			on_key(letter);
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