#include "drawingzone.h"

DrawingZone::DrawingZone() :
    QWidget(0)
{
    this->image=new QImage(800,600,QImage::Format_ARGB32_Premultiplied);
    this->prev_pos = QPoint(-666,-666);
}

DrawingZone::~DrawingZone()
{
    this->painter->end();
}

void DrawingZone::setPenSize(int i)
{
    pen.setWidth(i);
}

void DrawingZone::setPenColor(QColor color)
{
    pen.setColor(color);
}

void DrawingZone::paintEvent(QPaintEvent *event)
{
    this->painter = new QPainter(this);
        painter->setPen(pen);
        painter->drawImage(0,0,*(this->image));
}

void DrawingZone::mousePressEvent(QMouseEvent *event)
{
    this->mouseDown=true;
}

void DrawingZone::mouseReleaseEvent(QMouseEvent *event)
{
    this->mouseDown=false;
    this->prev_pos = QPoint(-666,-666);
}

void DrawingZone::mouseMoveEvent(QMouseEvent *event)
{
   if(this->mouseDown&&this->prev_pos.x()!=-666&&this->prev_pos.y()!=-666)
    {
        QPainter painter(this->image);
        painter.setPen(pen);
        painter.drawLine(this->prev_pos,event->pos());
        update();
    }
    this->prev_pos = event->pos();
}
