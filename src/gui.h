#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QGridLayout>
#include <QList>
#include <QStackedLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QCheckBox>
#include <QColorDialog>
#include <QLabel>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>

#include <controller.h>
#include <drawingzone.h>

namespace Ui {
class Gui;
}


class Gui : public QWidget
{
    Q_OBJECT
    Controller* controller;
    DrawingZone* drawingZone;
    //QPushButton* colorButton;
    QAction* colorButton;
    QColorDialog* colorPalette;

public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();

public slots:
    void showPicker();

private:
    Ui::Gui *ui;

    QMenu* fileMenu;
};

#endif // GUI_H
