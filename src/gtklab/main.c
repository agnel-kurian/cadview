#include <stdlib.h>
#include <gtk/gtk.h>

struct point_2d {
  double x;
  double y;
};

struct get_point_data {
  struct point_2d point;

  gulong button_press_handler_id;

};

gboolean get_point_button_press(GtkWidget* widget, GdkEvent *event,
  gpointer user_data){

  struct get_point_data *data = (struct get_point_data*)user_data;

  GdkEventButton *button_event = (GdkEventButton*)event;
  if(button_event->button == 1){
    data->point.x = button_event->x;
    data->point.y = button_event->y;

    g_signal_handler_disconnect(widget, data->button_press_handler_id);
    gtk_main_quit();
  }

  return FALSE;
}

struct point_2d getpoint(GtkWidget *widget){
  gchar* old_title = g_strdup(gtk_window_get_title(GTK_WINDOW(widget)));
  gtk_window_set_title (GTK_WINDOW (widget), "Select a point:");
  fprintf(stderr, "in getpoint\n");
  struct get_point_data data;
  data.button_press_handler_id =
    g_signal_connect(G_OBJECT(widget), "button-press-event",
      G_CALLBACK(get_point_button_press), &data);
  gtk_main();
  gtk_window_set_title (GTK_WINDOW (widget), old_title);
  g_free(old_title);
  return data.point;
}

  void menu_file_quit(GtkMenuItem *menuitem, gpointer user_data){
    fprintf(stderr, "quitting\n");
    gtk_main_quit();
  }

  void menu_file_pick(GtkMenuItem *menuitem, gpointer user_data){
    GtkWidget *widget = GTK_WIDGET(user_data);
    struct point_2d p = getpoint(widget);
    fprintf(stderr, "point = (%f,%f)\n", p.x, p.y);
  }

int main (int argc, char *argv[])
{
  fprintf(stderr, "in main\n");
  GtkWidget *win = NULL;
  GtkWidget *vbox = NULL;

  /* Initialize GTK+ */
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
  gtk_init (&argc, &argv);
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

  /* Create the main window */
  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_add_events(win, GDK_BUTTON_PRESS_MASK);
  g_signal_connect (G_OBJECT(win), "destroy", G_CALLBACK(menu_file_quit), NULL);

  gtk_window_set_title (GTK_WINDOW (win), "Hello World");
  gtk_window_set_default_size(GTK_WINDOW(win), 250, 200);

  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(win), vbox);

  GtkWidget *menubar = gtk_menu_bar_new();
  GtkWidget *filemenu = gtk_menu_new();
  GtkWidget *file = gtk_menu_item_new_with_mnemonic("_File");
  GtkWidget *pick = gtk_menu_item_new_with_mnemonic("_Pick a point...");
  g_signal_connect(G_OBJECT(pick), "activate",
    G_CALLBACK(menu_file_pick), win);
  GtkWidget *quit = gtk_menu_item_new_with_mnemonic("_Quit");
  g_signal_connect(G_OBJECT(quit), "activate",
    G_CALLBACK(menu_file_quit), NULL);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), pick);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);

  gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);

  gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
  gtk_widget_realize (win);


  /* Enter the main loop */
  gtk_widget_show_all (win);
  gtk_main ();
  return 0;
}
