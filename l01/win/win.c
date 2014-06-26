#include"win.h"

//{{{ int main(int argc,char **argv)
int main(int argc,char **argv)
{
	initdata();
	if(!g_thread_supported())
		g_thread_init(NULL);
	gdk_threads_init();
	gtk_init(&argc,&argv);
	gdk_threads_enter();
	crt_win();
	gdk_threads_leave();
//	gtk_main();
	return 0;
}//}}}

//{{{ int crt_win()
int crt_win()
{
	ws.win=gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(ws.win),"细胞生成机-gtk版");
	gtk_window_set_position(GTK_WINDOW(ws.win),GTK_WIN_POS_CENTER);
	gtk_widget_set_size_request(ws.win,width,height);
	gtk_window_set_resizable(GTK_WINDOW(ws.win),FALSE);
	ws.fixed=gtk_fixed_new();
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(ws.win)->vbox),ws.fixed,FALSE,FALSE,0);
	gtk_container_set_border_width(GTK_CONTAINER(ws.win),2);
	ws.bnt1=gtk_button_new_with_label("开始");
	//gtk_widget_set_sensitive(ws.mbnt[0],FALSE);设置禁用
	gtk_widget_set_size_request(ws.bnt1,bt_w,bt_h);
	gtk_fixed_put(GTK_FIXED(ws.fixed),ws.bnt1,bt1_x,bt1_y);
	ws.darea=gtk_drawing_area_new();
	gtk_widget_set_size_request(ws.darea,da_w,da_h);
	gtk_widget_set_app_paintable(ws.darea,TRUE);
	gtk_fixed_put(GTK_FIXED(ws.fixed),ws.darea,da_x,da_y);
	g_signal_connect(G_OBJECT(ws.bnt1),"clicked",G_CALLBACK(onbnt1),(gpointer)ws.darea);
	g_signal_connect(G_OBJECT(ws.darea),"expose-event",G_CALLBACK(on_drawing),NULL);
	gtk_widget_show_all(ws.win);
	gtk_dialog_run(GTK_DIALOG(ws.win));
	gtk_widget_destroy(ws.win);
	return 0;
}//}}}
//{{{ void onbnt1(GtkWidget *widget,gpointer gp)
void onbnt1(GtkWidget *widget,gpointer gp)
{
	char *lb;
	lb=(char*)gtk_button_get_label(GTK_BUTTON(widget));
	if(strncmp(lb,"开始",strlen(lb))==0)
	{
		if(ws.thread_lock==1)
			return;
		gtk_button_set_label(GTK_BUTTON(widget),"停止");
		ws.thread_lock=1;
		g_thread_create(goon,NULL,FALSE,NULL);
		return;
	}
	if(strncmp(lb,"停止",strlen(lb))==0)
	{
		if(ws.thread_lock==0)
			return;
		ws.thread_lock=0;
		pump();
		pump();
		gtk_button_set_label(GTK_BUTTON(widget),"开始");
		return;
	}
	//gtk_widget_queue_draw((GtkWidget*)gp);
}//}}}
//{{{ gboolean on_drawing(GtkWidget *widget,GdkEventExpose *event,gpointer gp)
gboolean on_drawing(GtkWidget *widget,GdkEventExpose *event,gpointer gp)
{
	int i,j,k;
	char ch[10];
	memset(ch,0,10);
	ch[0]='*';
	cairo_t *cr,*ct;
	ct=gdk_cairo_create(widget->window);
	cairo_set_source_rgb(ct,0,0,1);
	cairo_set_line_width(ct,0.5);
	cairo_set_font_size(ct,10);
	cr=gdk_cairo_create(widget->window);
	cairo_set_source_rgb(cr,0.85,0.85,0.85);
	cairo_set_line_width(cr,0.5);
	cairo_set_font_size(cr,10);
	cairo_rectangle(cr,0,0,da_w,da_h);
	cairo_fill(cr);
	for(i=0;i<XX;i++)
	{
		for(j=0;j<YY;j++)
		{
			if(b[j][i]==star)
			{
				cairo_move_to(ct,i*7,j*7);
				cairo_show_text(ct,ch);
			}
		}
	}
	cairo_stroke(ct);
	cairo_destroy(ct);
	cairo_stroke(cr);
	cairo_destroy(cr);
	return FALSE;
}//}}}

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
	if(flag!=2)
	{
		for(i=0;i<XX;i++)
		{
			for(j=0;j<YY;j++)
			{
				a[j][i]=nul;
				b[j][i]=nul;
			}
		}
	}
	ev_counts=lv_counts=0;
	rep=0;head=0;
	srand(time(0));
	/*for(j=0;j<=YY+1;j++)
	{
		move(j,9);
		echochar(shu);
		move(j,XX+10);
		echochar(shu);
		refresh();
	}
	for(i=10;i<XX+10;i++)
	{
		move(0,i);
		echochar(heng);
		move(YY+1,i);
		echochar(heng);
		refresh();
	}*/
	ws.thread_lock=0;
	return 0;
}//}}}

//{{{ void seed()
void seed()
{
	int i,j,k,m,n;
	char *c,name[128];
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
	if(flag==0)//save
	{
		c=&a[0][0];
		memset(name,0,sizeof(name));
		snprintf(name,sizeof(name),"%ld.sav",time(0));
		k=open(name,O_CREAT|O_RDWR,0644);
		if(k<=0)
			return;
		i=XX;j=YY;
		write(k,(void*)&i,4);
		write(k,(void*)&j,4);
		write(k,c,i*j);
		close(k);
	}
}//}}}

//{{{ gpointer goon(gpointer gp)
gpointer goon(gpointer gp)
{
	int i,j,k,m,n,v1,v2;
	char *c1,*c,ch;
	c=&b[0][0];
	c1=&a[0][0];
	if(flag!=2)
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
		lv_counts=0;/*
		for(i=0;i<XX;i++)
		{
			for(j=0;j<YY;j++)
			{
				move(j+1,i+10);
				echochar(b[j][i]);
				if(b[j][i]==star)
					lv_counts++;
			}
		}*//*
		lst[head++]=lv_counts;
		if(head>=10)
			head=0;
		n=0;
		for(m=0;m<10;m++)
		{
			if(lst[m]==lv_counts)
				n++;
		}
		if(n>2)
			rep++;
		else
			rep=0;
		ev_counts++;
		move(4,XX+15);
		printw("ev_counts: %04d",ev_counts);
		move(6,XX+15);
		printw("lv_counts: %04d",lv_counts);
		if(rep>60)
		{
			move(8,XX+15);
			printw("finished evolution!");
			move(10,XX+15);
			printw("press any key to exit..");
			refresh();
			break;
		}
		refresh();*/
		gdk_threads_enter();
		gtk_widget_queue_draw(ws.darea);
		gdk_threads_leave();
		pump();
		memcpy(c1,c,XX*YY);
		//break;
		if(ws.thread_lock==0)
			break;
	}
	return 0;
}//}}}




