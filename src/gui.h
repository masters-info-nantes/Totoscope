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
#include <QScrollArea>
#include <QPixmap>
#include <QTimer>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QFileDialog>
#include <QShortcut>


#include <controller.h>
#include <drawingzone.h>
#include <exportgui.h>
#include <thumbnail.h>

namespace Ui {
class Gui;
}


class Gui : public QWidget
{
    Q_OBJECT
    Controller* controller;
    DrawingZone* drawingZone;
    QLabel* frameWidget;
    QAction* playButton;
    QAction* pauseButton;
    QPushButton* colButton;
    QAction* colorButton;
    QColorDialog* colorPalette;
    QAction* vidAct;
    QAction* vidButton;
    QTimer* timer;
    QMenuBar* menuBar;
    QToolBar* topBar;
    QToolBar* leftBar;
    QScrollArea* scrollBar;


    public:
        explicit Gui(Controller*);
        ~Gui();

    public slots:
        void draw();
        void setPenSize(int);
        void erase();
        void showPicker();
        void changeColor(QColor);
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
        void showThumb(QString);
        void previousFrame();
        void nextFrame();
        void showMessage();

    private:
        Ui::Gui *ui;
};

#endif // GUI_H
