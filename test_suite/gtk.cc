#include <gtkmm.h>
#include <stdio.h>

class MyWindow : public Gtk::Window
{
public:
    MyWindow();
    ~MyWindow() override;

protected:
    void on_button_clicked();

    Gtk::Button m_button;
};

MyWindow::MyWindow() : m_button("Test")
{

    this->set_default_size(200, 200);

    m_button.set_margin(10);
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_button_clicked));

    set_child(m_button);
    
}

MyWindow::~MyWindow()
{
}

void MyWindow::on_button_clicked()
{
    printf("Hello World\n");
}

int main(int argc, char* argv[])
{
    g_setenv ("GTK_CSD", "0", false);
    auto app = Gtk::Application::create("com.gurtgames.Editor.gQuake");

    return app->make_window_and_run<MyWindow>(argc, argv);
}