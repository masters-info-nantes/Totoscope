#include "gui.h"
#include "splashgui.h"
#include <QApplication>
#include <controller.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Gui w;
    Controller* controller = new Controller();
    SplashGui w(controller);
    w.show();

    return a.exec();
}
