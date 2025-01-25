/**
 * @file main.c
 * @brief GTK4 Test 1
 * @date 01-25-2025
 * @par The second attempt to understand a GTK4 application. This time,
 * it's a bare application from scratch.
 */
#include <gtk/gtk.h>
#include "config.h"

#define MY_APP_WINDOW_TYPE (my_app_window_get_type())

typedef struct _MyAppWindow {
  GtkApplicationWindow parent_instance;
  GtkWidget *label0;
  GtkWidget *label1;
  GtkWidget *button0;
} MyAppWindow;

typedef struct _MyAppWindowClass {
  GtkApplicationWindowClass parent_class;
} MyAppWindowClass;

G_DEFINE_TYPE(MyAppWindow, my_app_window, GTK_TYPE_APPLICATION_WINDOW)

static void my_app_window_class_init(MyAppWindowClass *class) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(class);
  GError *error = NULL;
  char *contents;
  gsize length;

  if (g_file_get_contents("./src/resource/gtk4-test-1.ui", &contents, &length, &error)) {
    GBytes *template_bytes = g_bytes_new_take(contents, length);
    gtk_widget_class_set_template(widget_class, template_bytes);
    g_bytes_unref(template_bytes);

    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, label0);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, label1);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, button0);
  } else {
    g_error("Failed to load template: %s\n", error->message);
    g_error_free(error);
  }
}

static void my_app_window_init(MyAppWindow *self) {
  gtk_widget_init_template(GTK_WIDGET(self));
}

static void button_clicked_cb(GtkButton *button, MyAppWindow *self) {
  gtk_label_set_text(GTK_LABEL(self->label0), "Button was clicked!");
}

static void activate_cb(GtkApplication *app, gpointer user_data) {
  MyAppWindow *window = g_object_new(my_app_window_get_type(), "application", app, NULL);
  g_signal_connect(window->button0, "clicked", G_CALLBACK(button_clicked_cb), window);
  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
  GtkApplication *app;
  int status;

  // Disable accessibility
  g_setenv("GTK_A11Y", "none", TRUE);

  app = gtk_application_new("com.example.myapp", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate_cb), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
