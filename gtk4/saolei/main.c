#include <gtk/gtk.h>
#include <time.h>
#include <stdlib.h>

int boom[10][10]={0};
GtkWidget *button[100];

gboolean game_cheat(GtkWidget *widget,gpointer button_in)
{
    GtkWidget ** button=button_in;
    printf("%p ",button[0]);
    for (int i=0;i<10;i++)
    {
        for (int j=0;j<10;j++)
        {
            printf("%d ",boom[i][j]);
            if(boom[i][j]==1)
            gtk_button_set_label(button[i*10+j],"1");
            else
            gtk_button_set_label(button[i*10+j],"0");
        }
    }
}

gboolean begin_game(gpointer *widget)
{
    int random[10]={0};
    int count=0;
    int flag,t;

    srand((unsigned int)time(NULL));

    for (int i=0;i<10;i++)
    {
        random[i]=0;
    }

    while (count<10)
    {
        
        flag=0;
        t=rand()%100+1;
        for (int i=0;i<10;i++)
        {
            if (random[i]==t)
            {
                flag=1;
                break;
            }
        }
        if (flag==0)
        {
            random[count]=t;
            count++;
            printf("%d ",t);
        }
    }

    for (int i=0;i<10;i++)
    {
        for (int j=0;j<10;j++)
        {
            boom[i][j]=0;
        }
    }

    for (int i=0;i<10;i++)
    {
        boom[random[i]/10][random[i]%10]=1;
    }

}

static void activate (GtkApplication *app,gpointer user_data)
{
    int i=0,j=0;
    GtkWidget *window;
    GtkWidget *button_begin,*button_cheat;
    GtkWidget *grid,*grid_button;
    GtkWidget *box1,*box2;



    window=gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"扫雷");
    gtk_window_set_default_size(GTK_WINDOW(window),200,200);

    box1=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    box2=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    grid=gtk_grid_new();
    grid_button=gtk_grid_new();

    button_begin=gtk_button_new_with_label("begin");
    button_cheat=gtk_button_new_with_label("cheat");

    gtk_grid_attach(GTK_GRID(grid),grid_button,0,0,10,10);
    gtk_grid_attach(GTK_GRID(grid),button_begin,0,11,1,1);
    gtk_grid_attach(GTK_GRID(grid),button_cheat,1,11,1,1);

    for (i=0;i<10;i++)
    {
        for (j=0;j<10;j++)
        {
            button[10*i+j]=gtk_button_new();
        }
    }

    for (i=0;i<10;i++)
    {
        for (j=0;j<10;j++)
        {
            gtk_grid_attach(GTK_GRID(grid_button),button[i*10+j],j,i,1,1);
        }
    }

    
    gtk_window_set_child(GTK_WINDOW(window),grid);


    g_signal_connect(button_begin,"clicked",G_CALLBACK(begin_game),NULL);
    printf("%p ",button[0]);
    g_signal_connect(button_cheat,"clicked",G_CALLBACK(game_cheat),button);
    


    gtk_widget_show(window);
}


int main (int argc,char **argv)
{
    GtkApplication *app;
    int status;

    app=gtk_application_new("aor.gtk.example",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);
    
    g_object_unref(app);
}