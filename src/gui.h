#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaContent>
#include <QUrl>
#include <QFileDevice>
#include <QDir>
#include <QFile>
#include <QGridLayout>
#include <QVideoWidget>
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QPoint>
#include <QList>
#include <QVideoProbe>

namespace Ui {
class Gui;
}


class Gui : public QWidget
{
    Q_OBJECT

    QList<QVideoFrame>* list;
    int index;
    int framerate;
    bool mouseDown;
    QList<QPoint*>* drawings;
    QImage* image;
    QPoint prev_pos;

public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
public slots:
    void processFrame(QVideoFrame);
private:
    Ui::Gui *ui;
};

#endif // GUI_H
