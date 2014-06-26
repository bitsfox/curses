#include"win.h"


int main(int argc,char **argv)
{
	gtk_init(&argc,&argv);
	crt_win();
//	gtk_main();
	return 0;
}

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
}

void onbnt1(GtkWidget *widget,gpointer gp)
{
	if(flag==0)
		flag=1;
	else
		flag=0;
	gtk_widget_queue_draw((GtkWidget*)gp);
}
gboolean on_drawing(GtkWidget *widget,GdkEventExpose *event,gpointer gp)
{
	int i,j,k;
	cairo_t *cr;
	cr=gdk_cairo_create(widget->window);
	if(flag==0)
		cairo_set_source_rgb(cr,0,0,1);
	else
		cairo_set_source_rgb(cr,0,1,0);
	cairo_set_line_width(cr,0.5);
	cairo_rectangle(cr,da_x,da_y,da_w,da_h);
	cairo_fill(cr);
	cairo_stroke(cr);
	cairo_destroy(cr);
	return FALSE;
}




