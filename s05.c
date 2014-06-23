#include"clsscr.h"
#include<curses.h>

#define 	UP				0
#define		DOWN			1
#define		LEFT			2
#define		RIGHT			3
#define		star			'*'
#define		nul				' '
#define		num				100


struct POS
{
	int x;
	int y;
};
struct POS p[num];
int	head,tail,len;
char	sc[400][200];
int		dir[4];

void pump(int i);
int	 initdata();
int  get_dir();
void goon();

//{{{ int main(int argc,char** argv)
int main(int argc,char** argv)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr,true);
	if(initdata()!=0)
		goto end_01;
	goon();
end_01:
	getchar();
	endwin();
	return 0;
}//}}}

//{{{ void pump(int i)
void pump(int i)
{
	struct timeval tm;
	tm.tv_sec=0;
	tm.tv_usec=i*100000;
	select(0,NULL,NULL,NULL,&tm);
}//}}}
//{{{ int	 initdata()
int	 initdata()
{
	int i,j,k;
	for(i=0;i<num;i++)
		p[i].x=p[i].y=0;
	head=tail=len=0;
	if(COLS>=400 || LINES >= 200)
	{
		move(0,3);
		printw("the var your set is less than COLS OR LINES");
		refresh();
		return 1;
	}
	for(i=0;i<400;i++)
	{
		for(j=0;j<200;j++)
			sc[i][j]=nul;
	}
	srand(time(0));
	i=rand()%(LINES-2)+2;
	j=rand()%COLS;
	p[0].x=j;p[0].y=i;
	sc[j][i]=star;
	move(i,j);
	echochar(sc[j][i]);
	move(0,3);
	printw("times: ");
	move(0,COLS/2);
	printw("hello world");
	move(1,0);
	for(i=0;i<COLS;i++)
		addstr("-");
	refresh();
	return 0;
}//}}}
//{{{ int  get_dir()
int  get_dir()
{
	int i,j,k,l,m,n;
	for(i=0;i<4;i++)
		dir[i]=0;
	while(1)
	{
		m=0;n=0;
		for(i=0;i<4;i++)
		{
			if(dir[i]==-1)
				m++;
			else
				n=i;
		}
		if(m==4) //game over
			return 1;
		if(m==3) //only one dir
		{
			switch(n)
			{
				case UP://
					i=p[head].y-1;
					j=p[head].x;
					if(i<2)
						return 1;
					if(sc[i][j]==star)
						return 1;
					dir[UP]=1;
					return 0;
				case DOWN://
					i=p[head].y+1;
					j=p[head].x;
					if(i>LINES)
						return 1;
					if(sc[i][j]==star)
						return 1;
					dir[DOWN]=1;
					return 0;
				case LEFT://
					i=p[head].y;
					j=p[head].x-1;
					if(j<1)
						return 1;
					if(sc[i][j]==star)
						return 1;
					dir[LEFT]=1;
					return 0;
				case RIGHT:
					i=p[head].y;
					j=p[head].x+1;
					if(j>=COLS)
						return 1;
					if(sc[i][j]==star)
						return 1;
					dir[RIGHT]=1;
					return 0;

			};
			return 1;
		}
		k=rand()%4;
		switch(k)
		{
			case UP:
				if(dir[UP]==-1)
					continue;
				i=p[head].y-1;
				j=p[head].x;
				if(i<2)
				{
					dir[UP]=-1;
					continue;
				}
				if(sc[i][j]==star)
				{
					dir[UP]=-1;
					continue;
				}
				dir[UP]=1;
				return 0;
			case DOWN:
				if(dir[DOWN]==-1)
					continue;
				i=p[head].y+1;
				j=p[head].x;
				if(i>LINES)
				{
					dir[DOWN]=-1;
					continue;
				}
				if(sc[i][j]==star)
				{
					dir[DOWN]=-1;
					continue;
				}
				dir[DOWN]=1;
				return 0;
			case LEFT:
				if(dir[LEFT]==-1)
					continue;
				i=p[head].y;
				j=p[head].x-1;
				if(j<1)
				{
					dir[LEFT]=-1;
					continue;
				}
				if(sc[i][j]==star)
				{
					dir[LEFT]=-1;
					continue;
				}
				dir[LEFT]=1;
				return 0;
			case RIGHT:
				if(dir[RIGHT]==-1)
					continue;
				i=p[head].y;
				j=p[head].x+1;
				if(j>=COLS)
				{
					dir[RIGHT]=-1;
					continue;
				}
				if(sc[i][j]==star)
				{
					dir[RIGHT]=-1;
					continue;
				}
				dir[RIGHT]=1;
				return 0;
		};
	}
	return 0;
}//}}}
//{{{ void goon()
void goon()
{
	static int aa=0;
	int i,j,k,m,n;
	while(1)
	{
		i=get_dir();
		if(i==1)
			return;
		for(i=0;i<4;i++)
			if(dir[i]==1)
				break;
		switch(i)
		{
			case UP:
				while(1)//这是一种非常简单的逻辑实现，不能实现诸如：_|-|_之类的路线。
				{
					j=head;j++;
					if(j>=100)
						j=0;
					m=p[head].x;
					n=p[head].y-1;
					if(n<2)
						break;
					if(sc[n][m]==star)
						break;
					p[j].x=m;p[j].y=n;
					sc[n][m]=star;
					head=j;
					move(n,m);
					echochar(sc[n][m]);
					aa++;
					if(aa>6)
					{
						aa=0;
					}
					else
					{
						m=p[tail].x;
						n=p[tail].y;
						sc[n][m]=nul;
						tail++;
						if(tail>=100)
							tail=0;
						move(n,m);
						echochar(sc[n][m]);
					}
					refresh();
					pump(10);
				}
				break;
			case DOWN:
				while(1)
				{
					j=head;j++;
					if(j>=100)
						j=0;
					m=p[head].x;
					n=p[head].y+1;
					if(n>LINES)
						break;
					if(sc[n][m]==star)
						break;
					p[j].x=m;p[j].y=n;
					sc[n][m]=star;
					move(n,m);
					echochar(sc[n][m]);
					head=j;aa++;
					if(aa>6)
						aa=0;
					else
					{
						m=p[tail].x;
						n=p[tail].y;
						sc[n][m]=nul;
						tail++;
						if(tail>=100)
							tail=0;
						move(n,m);
						echochar(sc[n][m]);
					}
					refresh();
					pump(10);
				}
				break;
			case LEFT:
				while(1)
				{
					j=head;j++;
					if(j>=100)
						j=0;
					m=p[head].x-1;
					n=p[head].y;
					if(m<1)
						break;
					if(sc[n][m]==star)
						break;
					p[j].x=m;p[j].y=n;
					sc[n][m]=star;
					head=j;
					move(n,m);
					echochar(sc[n][m]);
					aa++;
					if(aa>6)
						aa=0;
					else
					{
						m=p[tail].x;
						n=p[tail].y;
						sc[n][m]=nul;
						tail++;
						if(tail>=100)
							tail=0;
						move(n,m);
						echochar(sc[n][m]);
					}
					refresh();
					pump(10);
				}
				break;
			case RIGHT:
				while(1)
				{
					j=head+1;
					if(j>=100)
						j=0;
					m=p[head].x+1;
					n=p[head].y;
					if(m>=COLS)
						break;
					if(sc[n][m]==star)
						break;
					p[j].x=m;p[j].y=n;
					sc[n][m]=star;
					head=j;
					move(n,m);
					echochar(sc[n][m]);
					aa++;
					if(aa>6)
						aa=0;
					else
					{
						m=p[tail].x;
						n=p[tail].y;
						sc[n][m]=nul;
						tail++;
						if(tail>=100)
							tail=0;
						move(n,m);
						echochar(sc[n][m]);
					}
					refresh();
					pump(10);
				}
				break;
		};
	}
}//}}}




