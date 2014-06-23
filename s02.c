#include"clsscr.h"
#include<curses.h>
//http://blog.csdn.net/byxdaz/article/details/1780449
struct pos
{
	int x;
	int y;
};
int settick();
int main(int argc,char **argv)
{
	struct pos p;
	char ch='*';
	int i,c;
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	//nonl();
	keypad(stdscr,true);
	move(0,3);
	printw("curses test!");
	move(1,0);
	for(i=0;i<COLS;i++)
		addstr("-");
	move(0,COLS/2-5);
	addstr("hello world");
	p.x=LINES/2;
	p.y=COLS/2;
	move(LINES/2,COLS/2);
	echochar(ch);
	while(1)
	{
		c = getch();
		if(c == 'q')
			break;
		if(c == 'a')
		{
			if(p.y<=2)
				continue;
			else
				p.y--;
		}
		if(c == KEY_UP)
		{
			if(p.x<=2)
				continue;
			else
				p.x--;
		}
		if(c == KEY_DOWN)
		{
			if(p.x>=(LINES-2))
				continue;
			else
				p.x++;
		}
		if(c == KEY_LEFT)
		{
			if(p.y <= 2)
				continue;
			else
				p.y--;
		}
		if(c == KEY_RIGHT)
		{
			if(p.y >= (COLS-2))
				continue;
			else
				p.y++;
		}
		move(p.x,p.y);
		printw("*");
		//echochar(ch);
		//settick();
		refresh();
	}
	endwin();
	return 0;
}
int settick()
{
	struct itimerval new_timeset;
	long n_sec, n_usecs;
	n_sec=20/1000;
	n_usecs=(20%1000)*100L;
	new_timeset.it_interval.tv_sec = n_sec;
	new_timeset.it_interval.tv_usec = n_usecs;
	n_sec = 1 / 1000 ;
	n_usecs = ( 1 % 1000 ) * 10L ;
	new_timeset.it_value.tv_sec = n_sec ;
	new_timeset.it_value.tv_usec = n_usecs ;
	return setitimer(ITIMER_REAL, &new_timeset, NULL);
};






