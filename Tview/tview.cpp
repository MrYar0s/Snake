#include "tview.hpp"
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <poll.h>
#include <signal.h>

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
	tcsetattr(0, TCSANOW, &old);
	clear();
}

void tview::clear()
{
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
	gotoxy(0, 0);
	hline(width - 1);
	gotoxy(0, 0);
	vline(height);
	gotoxy(0, height);
	hline(width - 1);
	gotoxy(width - 1, 0);
	vline(height);
}

void tview::setcolor(int color)
{
	std::cout << "\e[" << 48 << ";" << 5 << "m"<< "\e[" << color + 30 << "m"/*<< std::flush*/;
}

void tview::draw()
{
	refresh_stats();
	clear();
	setcolor(2);
	box(width, height);
	setcolor(3);
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