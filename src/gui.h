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
    QAction* playButton;
    QAction* pauseButton;
    QSpinBox *oignonSpin;
    QPushButton* colButton;
    QAction* colorButton;
    QAction *oignionAct;
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
        void resizeEvent();
        void setPenSize(int);
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
        void video();
        void showThumb(int);
        void previousFrame();
        void nextFrame();
        void showMessage();
        void updateDrawingZone();

    private:
        Ui::Gui *ui;
};

#endif // GUI_H
