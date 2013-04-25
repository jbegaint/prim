#include <gtk/gtk.h>
#include <gdk/gdkx.h>

#include <stdio.h>

#include "utils.h"

static void destroy( GtkWidget *widget, gpointer data )
{
    gtk_main_quit ();
}

static void open_file_button ( char *filename)
{
	printf("%s\n", filename);
}

static void choose_file ()
{

	GtkWidget *filechooser;
	GtkFileFilter *ff_txt;

	ff_txt = gtk_file_filter_new ();
	gtk_file_filter_set_name ( ff_txt, "txt");
	gtk_file_filter_add_pattern( ff_txt, "*.txt");

	filechooser = gtk_file_chooser_dialog_new ( "Choisir un fichier",
												NULL,
												GTK_FILE_CHOOSER_ACTION_OPEN,
												GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
												GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
												NULL);

	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (filechooser), ff_txt);

	if (gtk_dialog_run (GTK_DIALOG (filechooser)) == GTK_RESPONSE_ACCEPT) {
		char *filename;
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (filechooser));
		open_file_button(filename);
	}

	gtk_widget_destroy (filechooser);
}

static void create_toolbar ( GtkWidget *window, GtkWidget *vbox) 
{
	
	GtkWidget *toolbar;
	GtkToolItem *open;
	GtkToolItem *close;
	GtkToolItem *sep;
	GtkToolItem *quit;	

	toolbar = gtk_toolbar_new ();
	gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_ICONS);

	open = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), open, -1);

	close = gtk_tool_button_new_from_stock(GTK_STOCK_CLOSE);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), close, -1);

	sep = gtk_separator_tool_item_new();
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);

	quit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), quit, -1);


	gtk_box_pack_start(GTK_BOX (vbox), toolbar, FALSE, FALSE, 2);

	g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);
    g_signal_connect(G_OBJECT (quit), "clicked", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT (open), "clicked", choose_file, NULL);

}

int main (int argc, char** argv)
{
	GtkWidget *main_window;
	GtkWidget *vbox;


	gtk_init (&argc, &argv);
	 
	main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (main_window), "Voyageur de commerce 1.0");
	gtk_window_set_position (GTK_WINDOW (main_window), GTK_WIN_POS_CENTER );
	gtk_window_resize (GTK_WINDOW (main_window), 500, 500);

	vbox = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER (main_window), vbox);
	create_toolbar (main_window, vbox);

  
    gtk_widget_show_all (main_window);

    gtk_main ();
    
    return 0;
}