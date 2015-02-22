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
    QAction* playButton;
    QAction* pauseButton;
    QAction* colorButton;
    QColorDialog* colorPalette;


    public:
        explicit Gui(Controller*);
        ~Gui();

    public slots:
        void draw();
        void setPenSize(int);
        void erase();
        void showPicker();
        void undo();
        void redo();
        void newProject();
        void openProject();
        void save();
        void saveAs();
        void imgExport();
        void vidExport();
        void closeProject();
        void stop();
        void playDraw();
        void pauseDraw();
        void playPause();
        void next();
        void pelures();
        void video();

    private:
        Ui::Gui *ui;
};

#endif // GUI_H
