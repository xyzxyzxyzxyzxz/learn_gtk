#include <gtk/gtk.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

char timestr[100]={0};

static void print_time(GtkWidget *widget,gpointer data)
{
    g_print("%s",data);
}

void time_now()
{
        time_t timep;        

        time (&timep); 

        strcpy(timestr,asctime( gmtime(&timep) ) );
}

gboolean show_time(gpointer *label)
{
    time_now();
    gtk_label_set_text(GTK_LABEL(label),timestr);
}

static void activate (GtkApplication *app,gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button,*button_exit;
    GtkWidget *box1,*box2;
    GtkWidget *label;
    GtkWidget *grid;

    window=gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"time");
    gtk_window_set_default_size(GTK_WINDOW(window),200,200);

    grid=gtk_grid_new();


    box1=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    box2=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_window_set_child(GTK_WINDOW(window),grid);
    //gtk_window_set_child(GTK_WINDOW(window),box1);
    gtk_grid_attach(GTK_GRID(grid),box1,0,0,1,1);
    gtk_grid_attach(GTK_GRID(grid),box2,0,1,1,1);

    
    button_exit=gtk_button_new_with_label("exit");
    label=gtk_label_new_with_mnemonic("zheshishijian");
    
    time_now();

    g_signal_connect(button_exit,"clicked",G_CALLBACK(print_time),timestr);
    g_signal_connect_swapped(button_exit,"clicked",G_CALLBACK(gtk_window_destroy),window);
    gtk_box_append(GTK_BOX(box1),label);
    gtk_box_append(GTK_BOX(box2),button_exit);

    g_timeout_add(100,(GSourceFunc)show_time,(gpointer)label);

    gtk_widget_show(window);


}

int main (int argc,char **argv)
{
    GtkApplication *app;
    int status;

    app=gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);

    return status;    
}