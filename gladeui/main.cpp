#include <stdlib.h>
#include <gtk/gtk.h>
#include "slate.h"

#include <iostream>

using std::cerr;

void menu_file_quit(GtkMenuItem *menuitem, gpointer user_data){
  cerr << "quitting\n";
  gtk_main_quit();
}

void menu_file_select(GtkMenuItem *menuitem, gpointer user_data){
  cad_core::cad_gui_view<double,
    cad_core::cad_gtk_adaptor<double> > *view =
    (cad_core::cad_gui_view<double,
      cad_core::cad_gtk_adaptor<double> >*) user_data;
  view->run_select_cmd();
}

void menu_file_polyline(GtkMenuItem *menuitem, gpointer user_data){
  cad_core::cad_gui_view<double,
    cad_core::cad_gtk_adaptor<double> > *view =
    (cad_core::cad_gui_view<double,
      cad_core::cad_gtk_adaptor<double> >*) user_data;
  view->run_polyline_cmd();

}

int main (int argc, char *argv[])
{
  GtkBuilder *builder;
  GtkWidget *window;
  GtkWidget *quit;
  GtkWidget *select;
  GtkWidget *polyline;
  GtkWidget *slate;
  GtkWidget *vbox;

  gtk_init (&argc, &argv);

  builder = gtk_builder_new ();
  gtk_builder_add_from_file (builder, "cadview.glade", NULL);
  window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
  g_signal_connect(G_OBJECT(window), "destroy",
    G_CALLBACK(menu_file_quit), NULL);
  quit = GTK_WIDGET(gtk_builder_get_object(builder, "quit"));
  select = GTK_WIDGET(gtk_builder_get_object(builder, "select"));
  polyline = GTK_WIDGET(gtk_builder_get_object(builder, "polyline"));
  vbox = GTK_WIDGET(gtk_builder_get_object(builder, "vbox"));

  slate = gtk_slate_new();

  g_signal_connect(G_OBJECT(quit), "activate",
    G_CALLBACK(menu_file_quit), NULL);

  cad_core::cad_document<double> document;
  cad_core::cad_gtk_adaptor<double> gui(slate);
  cad_core::cad_gui_view<double,
    cad_core::cad_gtk_adaptor<double> > view(document, gui);
  gtk_slate_set_view(slate, &view);

  g_signal_connect(G_OBJECT(select), "activate",
    G_CALLBACK(menu_file_select), &view);
  g_signal_connect(G_OBJECT(polyline), "activate",
    G_CALLBACK(menu_file_polyline), &view);

  GtkWidget *placeholder = GTK_WIDGET(gtk_builder_get_object(builder, "placeholder"));
  gtk_container_remove(GTK_CONTAINER(vbox), GTK_WIDGET(placeholder));

  gtk_box_pack_start(GTK_BOX(vbox), slate, TRUE, TRUE, 0);
  gtk_box_reorder_child(GTK_BOX(vbox), slate, 1);

  g_object_unref (G_OBJECT (builder));

  gtk_widget_show_all (window);
  gtk_main ();

  return 0;
}
