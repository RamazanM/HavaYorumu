#include <gtk/gtk.h>
#include <string.h>
#include "asprintf.c"
#include "vasprintf-c99.c"


static void activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *container;
  GtkWidget *hava_durumu;
  GtkWidget *gorsel;
  char *hava_string;

  asprintf(&hava_string,"Hava Sıcaklığı: %d °C\n\nRüzgar hızı:%d km/s",hava.sicaklik,hava.ruzgar);

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "HavaYorumu");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gorsel=gtk_image_new_from_file("HeavyRain.gif");
  container = gtk_box_new (GTK_ORIENTATION_VERTICAL,2);
  gtk_container_add (GTK_CONTAINER (window), container);
  gtk_container_add (GTK_CONTAINER (container), gorsel);



hava_durumu=gtk_label_new(hava_string);
gtk_container_add(GTK_CONTAINER(container),hava_durumu);

  gtk_widget_show_all (window);
}

// int
// main (){
//   GtkApplication *app;
//   int status;
//
//   app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
//   g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
//   status = g_application_run (G_APPLICATION (app), 0, NULL);
//   g_object_unref (app);
//
//   return status;
// }
