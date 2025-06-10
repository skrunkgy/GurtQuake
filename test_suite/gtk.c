#include <gtk/gtk.h>

static void activate( GtkApplication *app, gpointer userdata )
{
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Editor");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    GtkWidget *button = gtk_button_new_with_label("ASS");
    gtk_widget_set_size_request(button, 30, 20);
    gtk_window_set_child(GTK_WINDOW(window), button);

    gtk_window_present(GTK_WINDOW(window));

}

int main(int argc, char** argv)
{
    GtkApplication* app;

    app = gtk_application_new("com.gurtgames.gqeditor", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref (app);
}