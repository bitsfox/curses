/*二维细胞生成机代码
 
 				Author:tybitsfox	2014-6-24

 */

#include"clsscr.h"
#include<curses.h>

#define		XX			100
#define		YY			40
#define		nul			' '
#define		star		'*'
#define		shu			'|'
#define 	heng		'-'
#define		timz		200000
#define		seed_num	300
char a[YY][XX],b[YY][XX];


//{{{ void pump()
void pump()
{
	struct timeval tm;
	tm.tv_sec=0;
	tm.tv_usec=timz;
	select(0,NULL,NULL,NULL,&tm);
}//}}}
//{{{ int initdata()
int initdata()
{
	int i,j,k;
	for(i=0;i<XX;i++)
	{
		for(j=0;j<YY;j++)
		{
			a[j][i]=nul;
			b[j][i]=nul;
		}
	}
	srand(time(0));
	for(j=2;j<=YY+3;j++)
	{
		move(j,9);
		echochar(shu);
		move(j,XX+10);
		echochar(shu);
		refresh();
	}
	for(i=10;i<XX+10;i++)
	{
		move(2,i);
		echochar(heng);
		move(YY+3,i);
		echochar(heng);
		refresh();
	}
	return 0;
}//}}}
//{{{ void seed()
void seed()
{
	int i,j,k,m,n;
	for(i=0;i<YY;i++)
	{
		for(j=0;j<XX;j++)
		{
			a[i][j]=nul;
			b[i][j]=nul;
		}
	}
	i=rand()%seed_num+seed_num;
	for(j=0;j<i;j++)
	{
		k=rand()%(XX*YY);
		m=k/XX;n=k%XX;
		a[m][n]=star;
	}
}//}}}
int goon();

//{{{ int main(int argc,char **argv)
int main(int argc,char **argv)
{
	int i,j,k;
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr,true);
	if(COLS<=XX || LINES<=YY)
	{
		move(LINES/2,COLS/2-10);
		printw("window size is to small");
		refresh();
		goto end_01;
	}
	initdata();
	//seed();
	goon();/*
	for(i=0;i<XX;i++)
	{
		for(j=0;j<YY;j++)
		{
			move(j+3,i+10);
			echochar(a[j][i]);
		}
	}
	refresh();*/
end_01:	
	k=getchar();
	endwin();
	return 0;
}//}}}
//{{{ int goon()
int goon()
{
	static int st=0;
	int i,j,k,m,n,v1,v2;
	char *c1,*c,ch;
	c=&b[0][0];
	c1=&a[0][0];
	seed();
	while(1)
	{
		memset(c,nul,XX*YY);
		for(i=0;i<XX;i++)
		{
			for(j=0;j<YY;j++)
			{
				m=n=0;
				if(j>0)
				{
					if(i>0)
					{
						if(a[j-1][i-1]==star)
							m++;
					}
					if(a[j-1][i]==star)
						m++;
					if(i<(XX-1))
					{
						if(a[j-1][i+1]==star)
							m++;
					}
				}
				if(i>0)
				{
					if(a[j][i-1]==star)
						m++;
				}
				if(i<(XX-1))
				{
					if(a[j][i+1]==star)
						m++;
				}
				if(j<(YY-1))
				{
					if(i>0)
						if(a[j+1][i-1]==star)
							m++;
					if(a[j+1][i]==star)
						m++;
					if(i<(XX-1))
						if(a[j+1][i+1]==star)
							m++;
				}
				if(m==2)
					b[j][i]=a[j][i];
				else
				{
					if(m==3)
						b[j][i]=star;
					else
						b[j][i]=nul;
				}
			}
		}
		for(i=0;i<XX;i++)
		{
			for(j=0;j<YY;j++)
			{
				move(j+3,i+10);
				echochar(b[j][i]);
			}
		}
		refresh();
		pump();
		memcpy(c1,c,XX*YY);
		//break;
	}
	return 0;
}//}}}




