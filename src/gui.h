#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QGridLayout>
#include <QList>
#include <QStackedLayout>
#include <controller.h>
#include <drawingzone.h>
#include <QPushButton>
#include <QLabel>

namespace Ui {
class Gui;
}


class Gui : public QWidget
{
    Q_OBJECT
    Controller* controller;
    DrawingZone* drawingZone;
public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();


private:
    Ui::Gui *ui;
};

#endif // GUI_H
