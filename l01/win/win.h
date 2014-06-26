#include"clsscr.h"
#include<gtk/gtk.h>

struct win_struct
{
	GtkWidget *win;
	GtkWidget *fixed;
	GtkWidget *bnt1;
	GtkWidget *bnt2;
	GtkWidget *bnt3;
	GtkWidget *bnt4;
	GtkWidget *darea;
	GtkWidget *dpic;
	int		thread_lock;
};

#define		width					800
#define		height					800
#define		bt1_x					5
#define		bt1_y					15
#define		bt_w					50
#define		bt_h					23
#define		bt2_x					bt1_x
#define		bt2_y					bt1_y+bt_h+3
#define		bt3_x					bt2_x
#define		bt3_y					bt2_y+bt_h+3
#define		bt4_x					bt3_x
#define		bt4_y					bt3_y+bt_h+3

#define		da_x					bt1_x+bt_w+10
#define		da_y					bt1_y
#define		da_w					700
#define		da_h					700

#define		dp_x					da_x
#define		dp_y					da_y+da_h+20
#define		dp_w					da_w
#define		dp_h					200

struct win_struct  ws;
//原cli版本的定义
#define		XX			100
#define		YY			100
#define		nul			' '
#define		star		'*'
#define		shu			'|'
#define 	heng		'-'
#define		timz		200000
#define		seed_num	XX*YY/10

char a[YY][XX],b[YY][XX];
int  flag=0;
int	 ev_counts=0;			//进化次数
int	 lv_counts=0;			//生存数量
int  rep=0;					//重复次数。
int  lst[10]={0};			//最后10次的生存数量
int  head;					//list的头指针

//----------------------------------------------------------
int crt_win();
int main(int argc,char **argv);
void onbnt1(GtkWidget *widget,gpointer gp);
gboolean on_drawing(GtkWidget *widget,GdkEventExpose *event,gpointer gp);

//原函数
void pump();
int initdata();
void seed();
gpointer  goon(gpointer gp);


