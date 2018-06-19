#include "drawFunc.h"

void drawCell (cairo_t *cr, int r, int g, int b, int x, int y, int size) {
  cairo_set_source_rgb (cr, r, g, b);
  cairo_rectangle (cr, x * size, y * size, size, size);
  cairo_fill (cr);
}

void drawCells (cairo_t *cr) {
  int x, y;
  for (x = 0; x < cellCount; x++) {
    for (y = 0; y < cellCount; y++) {
      int s = cells[x][y].currentState;
      int r, g, b;
      
      /*
       * Red is Infected, green is Suscetipble
       * Blue is Recovered, Black is Dead
       */
      if (s == 0) {
	r = 1;
	g = 0;
	b = 0;
      } else if (s == 1) {
	r = 0;
	g = 1;
	b = 0;
      } else if (s == 2) {
	r = 0;
	g = 0;
	b = 1;
      } else {
	r = 0;
	g = 0;
	b = 0;
      }

      drawCell (cr, r, g, b, x, y, windowSize / cellCount);
    }
  }

  runIteration();
}

void draw (cairo_t *cr) {
  drawCells (cr);
  gtk_widget_queue_draw (drawArea);
}

static gboolean onDraw (GtkWidget *widget, cairo_t *cr, gpointer user_data) {
  draw (cr);
  return FALSE;
}

void createWindow (GtkApplication* app, gpointer user_data) {
  GtkWidget *window = gtk_application_window_new (app);

  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size (GTK_WINDOW (window), windowSize, windowSize);
  gtk_window_set_title (GTK_WINDOW (window), "Ebola Virus");

  drawArea = gtk_drawing_area_new ();
  gtk_container_add (GTK_CONTAINER (window), drawArea);
  g_signal_connect (G_OBJECT (drawArea), "draw", G_CALLBACK (onDraw), NULL);

  gtk_widget_show_all (window);
}
