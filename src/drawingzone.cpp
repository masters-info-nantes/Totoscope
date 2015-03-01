#include "drawingzone.h"

DrawingZone::DrawingZone() :
    QWidget(0)
{
    this->setStyleSheet("border:2px solid black;");

    this->layout = new QStackedLayout();
    this->layout->setStackingMode(QStackedLayout::StackAll);
    this->setLayout(this->layout);
    //this->image=new QImage(this->width(),this->height(),QImage::Format_ARGB32_Premultiplied);
    this->onions  = new QList<QPixmap*>();
    this->videoFrameContainer = new QLabel();
    this->videoFrameContainer->setStyleSheet("border:10px solid green");
    this->videoFrameContainer->setFixedSize(this->width(),this->height());
    //this->layout->addWidget(this->videoFrameContainer);
    this->drawingContainer = new QLabel();
    this->drawingContainer->setStyleSheet("border:2px solid red");
    this->drawingContainer->setFixedSize(this->width(),this->height());
    this->layout->addWidget(this->drawingContainer);
    this->layout->setCurrentWidget(this->drawingContainer);
    this->prev_pos = QPoint(-666,-666);
    pen.setWidth(3);
    this->isRubber = false;
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

void DrawingZone::mousePressEvent(QMouseEvent *event)
{
    this->mouseDown=true;
    updatePrevImage();
}

void DrawingZone::mouseReleaseEvent(QMouseEvent *event)
{
    this->mouseDown=false;
    this->prev_pos = QPoint(-666,-666);

}

void DrawingZone::mouseMoveEvent(QMouseEvent *event)
{
    QPoint *pos = new QPoint(event->pos().x()/this->ratioX,event->pos().y()/this->ratioY);
   if(this->mouseDown&&this->prev_pos.x()!=-666&&this->prev_pos.y()!=-666)
    {
        QPainter painter(this->image);
        if(isRubber)
            painter.setCompositionMode(QPainter::CompositionMode_Clear);
        painter.setPen(pen);

        painter.drawLine(this->prev_pos,*pos);
        //update();
        this->drawingContainer->setPixmap(QPixmap::fromImage(*(this->image)).scaled(this->width(),this->height()));
    }
    this->prev_pos = *pos;
}
void DrawingZone::setImage(QImage* anImage)
{
    this->image = anImage;
    this->drawingContainer->setPixmap(QPixmap::fromImage(*(this->image)).scaled(this->width(),this->height()));
    this->ratioX = this->width()/this->image->width();
    this->ratioY = this->height()/this->image->height();
}

void DrawingZone::setVideoFrame(QPixmap* pix)
{
    this->videoFrame = pix;
    this->videoFrameContainer->setPixmap(pix->scaled(this->width(),this->height()));
}

void DrawingZone::updatePrevImage()
{
    this->prev_image = new QImage(*(this->image));

}

void DrawingZone::undoImage()
{
    qDebug("Retour chef!");
    this->image = new QImage(*(this->prev_image));
    this->drawingContainer->setPixmap(QPixmap::fromImage(*(this->image)).scaled(this->width(),this->height()));
}

QImage* DrawingZone::getImage()
{
    return this->image;
}

void DrawingZone::choosePen()
{
    this->isRubber = false;
}

void DrawingZone::chooseRubber()
{
    this->isRubber = true;
}

void DrawingZone::resizeEvent()
{
        this->videoFrameContainer->setFixedSize(this->width(),this->height());
        this->drawingContainer->setFixedSize(this->width(),this->height());
        this->drawingContainer->setPixmap(QPixmap::fromImage(*(this->image)).scaled(this->width(),this->height()));
        this->videoFrameContainer->setPixmap(this->videoFrame->scaled(this->width(),this->height()));
}

void DrawingZone::showOnions(QList<QImage*>* onions)
{
    QLayoutItem *item;
    while((item = this->layout->takeAt(0)))
    {
        this->layout->removeItem(item);
    }
    this->layout->addWidget(this->videoFrameContainer);
    for(int i=0; i<onions->length();i++)
    {
        QLabel* lab= new QLabel();
        lab->setPixmap(QPixmap::fromImage(onions->at(i)->scaled(this->width(),this->height())));
        this->layout->addWidget(lab);
    }
    this->layout->addWidget(this->drawingContainer);
    this->layout->setCurrentWidget(this->drawingContainer);
}

void DrawingZone::hideOnions()
{
    QLayoutItem *item;
    while((item = this->layout->takeAt(0)))
    {
        this->layout->removeItem(item);
    }
    this->layout->addWidget(this->videoFrameContainer);
    this->layout->addWidget(this->drawingContainer);
    this->layout->setCurrentWidget(this->drawingContainer);
}

void DrawingZone::showVideo()
{
    this->videoFrameContainer->show();
}

void DrawingZone::hideVideo()
{
    this->videoFrameContainer->hide();
}
