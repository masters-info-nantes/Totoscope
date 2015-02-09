#ifndef DRAWINGZONE_H
#define DRAWINGZONE_H

#include <QWidget>
 #include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>

class DrawingZone : public QWidget
{
    Q_OBJECT

    QPoint prev_pos;
    QPainter* painter;
    bool mouseDown;
    QImage* image;
public:
    explicit DrawingZone();
    ~DrawingZone();
signals:

public slots:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
};

#endif // DRAWINGZONE_H
