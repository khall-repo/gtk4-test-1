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

  GtkWidget *col_header_label0;
  GtkWidget *col_header_label1;

  GtkWidget *data_display_label0;
  GtkWidget *data_display_label1;
  GtkWidget *data_display_label2;
  GtkWidget *data_display_label3;
  GtkWidget *data_display_label4;
  GtkWidget *data_display_label5;
  GtkWidget *data_display_label6;
  GtkWidget *data_display_label7;
  GtkWidget *data_display_label8;
  GtkWidget *data_display_label9;
  GtkWidget *data_display_label10;
  GtkWidget *data_display_label11;
  GtkWidget *data_display_label12;
  GtkWidget *data_display_label13;
  GtkWidget *data_display_label14;
  GtkWidget *data_display_label15;
  
  GtkWidget *button0; // bottom button

  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *button3;
  GtkWidget *button4;
  GtkWidget *button5;
  GtkWidget *button6;
  GtkWidget *button7;
  GtkWidget *button8;

  GtkWidget *button9;
  GtkWidget *button10;
  GtkWidget *button11;
  GtkWidget *button12;
  GtkWidget *button13;
  GtkWidget *button14;
  GtkWidget *button15;
  GtkWidget *button16;

} MyAppWindow;

typedef struct _MyAppWindowClass {
  GtkApplicationWindowClass parent_class;
} MyAppWindowClass;

// This macro will actually take the string "my_app_window" and converts it to
// "my_app_window_class_init" and "my_app_window_init", and stores those names
// internally. That is how GTK knows where to find the class and init
// functions in here! Terrible for the uninitiated.
G_DEFINE_TYPE(MyAppWindow, my_app_window, GTK_TYPE_APPLICATION_WINDOW)

static void my_app_window_class_init(MyAppWindowClass *class) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(class);
  GError *error = NULL;
  char *contents;
  gsize length;

  // Load the template from the file. Alternatively, you can compile the UI and
  // store it as a GResource, but that's a bit more complicated. See the howto
  // file I included in this project's root directory called
  // compiled-ui-resources-howto.txt.
  if (g_file_get_contents("./src/resource/gtk4-test-1.ui", &contents, &length, &error)) {
    GBytes *template_bytes = g_bytes_new_take(contents, length);
    gtk_widget_class_set_template(widget_class, template_bytes);
    g_bytes_unref(template_bytes);

    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, col_header_label0);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, col_header_label1);

    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, data_display_label0);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, data_display_label1);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, data_display_label2);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, data_display_label3);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, data_display_label4);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, data_display_label5);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, data_display_label6);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, data_display_label7);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, data_display_label8);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, data_display_label9);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, data_display_label10);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, data_display_label11);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, data_display_label12);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, data_display_label13);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, data_display_label14);
    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, data_display_label15);

    gtk_widget_class_bind_template_child(widget_class, MyAppWindow, button0);
  } else {
    g_error("Failed to load template: %s\n", error->message);
    g_error_free(error);
  }
}

static void my_app_window_init(MyAppWindow *self) {
  gtk_widget_init_template(GTK_WIDGET(self));
}

static void button0_clicked_cb(GtkButton *button, MyAppWindow *self) {
  gtk_label_set_text(GTK_LABEL(self->data_display_label0), "Button0 was clicked!");
}

static void activate_cb(GtkApplication *app, gpointer user_data) {
  MyAppWindow *window = g_object_new(my_app_window_get_type(), "application", app, NULL);

  // Connect the button0 signal its the callback function
  g_signal_connect(window->button0, "clicked", G_CALLBACK(button0_clicked_cb), window);
  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
  GtkApplication *app;
  int status;

  // Disable accessibility
  g_setenv("GTK_A11Y", "none", TRUE);

  // So this is weird.. on the RPi OS, it complains that
  // G_APPLICATION_FLAGS_NONE is deprecated, and that we should use
  // G_APPLICATION_DEFAULT_FLAGS. But on Linux mint AMD64, that doesn't even
  // exist.
  app = gtk_application_new("com.example.myapp", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate_cb), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
