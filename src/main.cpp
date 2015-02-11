#include "gui.h"
#include "splashgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Gui w;
    SplashGui w;
    w.show();

    return a.exec();
}
