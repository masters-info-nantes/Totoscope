#ifndef DRAWINGZONE_H
#define DRAWINGZONE_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QStackedLayout>
#include <QImage>
#include <QPixmap>
#include <QList>
#include <QLabel>

class DrawingZone : public QWidget
{
    Q_OBJECT
    QStackedLayout* layout;
    QPoint prev_pos;
    QPainter* painter;
    QPen pen;
    bool mouseDown;
    QLabel* videoFrameContainer;
    QLabel* drawingContainer;
    QPixmap* videoFrame;
    QList<QPixmap*>* onions;
    QImage* image;
    QImage* prev_image;
    bool isRubber;
    float ratioX;
    float ratioY;
public:
    explicit DrawingZone();
    void setPenSize(int);
    void setPenColor(QColor);

    void setImage(QImage*);
    void setVideoFrame(QPixmap*);
    void updatePrevImage();

    QImage* getImage();
    void showOnions(QList<QImage*>*);
    void hideOnions();
    void showVideo();
    void hideVideo();
    ~DrawingZone();

public slots:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void resizeEvent();
    void choosePen();
    void chooseRubber();
    void undoImage();
};

#endif // DRAWINGZONE_H
