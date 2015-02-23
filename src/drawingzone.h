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
    QPen pen;
    bool mouseDown;
    QImage* image;
    QImage* prev_image;

public:
    explicit DrawingZone();
    void setPenSize(int);
    void setPenColor(QColor);
    void setImage(QImage*);
    void updatePrevImage();
    void undoImage();
    QImage* getImage();
    ~DrawingZone();

public slots:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
};

#endif // DRAWINGZONE_H
