#include "tview.hpp"
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <poll.h>

termios old;
bool final = false;

tview::tview()
{
	printf("TEXT VIEW STARTED\n");
	fflush(stdout);
	tcgetattr(0, &old);
	termios start = old;
	cfmakeraw(&start);
	start.c_lflag |= ISIG;
	tcsetattr(0, TCSANOW, &start);
}

tview::~tview()
{
	tcsetattr(0, TCSANOW, &old);
	clear();
}

void tview::clear()
{
	printf("\e[H\e[J");
	fflush(stdout);
}

void tview::puts(const char* s)
{
	printf("%s", s);
	fflush(stdout);
}

void tview::putc(char c)
{
	printf("%c", c);
	fflush(stdout);
}

void tview::gotoxy(int x, int y)
{
	printf("\e[%d;%dH", y, x);
	fflush(stdout);
}

void tview::gline(int x, int y)
{
	for(int i = 0; i < width; i++)
	{
		gotoxy(x + i, y);
		printf("#");
		fflush(stdout);
	}
}

void tview::hline(int x, int y)
{
	for(int i = 0; i < height; i++)
	{
		gotoxy(x, i + y);
		printf("#");
		fflush(stdout);
	}
}

void tview::setcolor(int color)
{
	printf("\e[%dm", color + 30);
	fflush(stdout);
}

void tview::draw()
{
	refresh_stats();
	clear();
	setcolor(2);
	gline(0, 0);
	gline(0, height);
	hline(0, 0);
	hline(width, 0);
	setcolor(3);
	gotoxy(width/2, 0);
	puts("SNAKE");
}

void onsig(int sig)
{
	final = true;
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
	signal(SIGINT, onsig);
	pollfd fds[1];
	fds[0].fd = 0;
	fds[0].events = POLLIN;
	int n;
	while(!final)
	{
		n = poll(fds, 1, 500);
		if(n == 1)
		{
			unsigned char letter = getchar();
			on_key(letter);
		}
		if(n == 0)
		{
			draw();
		}
	}
}