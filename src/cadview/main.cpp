#include <gtk/gtk.h>
#include "slate.h"

void menu_file_quit(GtkMenuItem *menuitem, gpointer user_data){
  fprintf(stderr, "quitting\n");
  gtk_main_quit();
}

gboolean cadview_mouse_release(GtkWidget *widget, GdkEventButton *event,
  gpointer user_data){

  cad_core::Mouse_button button = Mouse_button_from_Gtk(event->button);
  GtkSlate *slate = GTK_SLATE(widget);
  cad_core::cad_gui_view<double,
    cad_core::cad_gtk_adaptor<double> >& view = *(slate->view);
  if(view.get_input() != 0)
    return FALSE;

  if(button == cad_core::Mouse_button_Right)
    view.run_polyline_cmd();

  return FALSE;

}

int main(int argc, char *argv[]){
  GtkWidget *window;
  GtkWidget *slate;
  GtkWidget *vbox;
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 180);

  slate = gtk_slate_new();

  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  GtkWidget *menubar = gtk_menu_bar_new();
  GtkWidget *filemenu = gtk_menu_new();
  GtkWidget *file = gtk_menu_item_new_with_mnemonic("_File");
  GtkWidget *quit = gtk_menu_item_new_with_mnemonic("_Quit");
  g_signal_connect(G_OBJECT(quit), "activate",
    G_CALLBACK(menu_file_quit), NULL);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);

  gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(vbox), slate, TRUE, TRUE, 0);

  g_signal_connect(G_OBJECT(window), "destroy",
    G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(window), "destroy",
    G_CALLBACK(gtk_widget_destroyed), &window);

  g_signal_connect(G_OBJECT(slate), "button-release-event",
    G_CALLBACK(cadview_mouse_release), 0);

  cad_core::cad_document<double> document;
  cad_core::cad_gtk_adaptor<double> gui(slate);
  cad_core::cad_gui_view<double,
    cad_core::cad_gtk_adaptor<double> > view(document, gui);
  gtk_slate_set_view(slate, &view);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
