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

};

#define		width					800
#define		height					700
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
#define		da_h					450

#define		dp_x					da_x
#define		dp_y					da_y+da_h+20
#define		dp_w					da_w
#define		dp_h					200

#define		XX						100
#define		YY						40

struct win_struct  ws;
int   flag=0;
char	ch[YY][XX];

//----------------------------------------------------------
int crt_win();
int main(int argc,char **argv);
void onbnt1(GtkWidget *widget,gpointer gp);
gboolean on_drawing(GtkWidget *widget,GdkEventExpose *event,gpointer gp);




