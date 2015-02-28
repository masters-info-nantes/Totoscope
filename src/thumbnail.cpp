#include "thumbnail.h"


Thumbnail::Thumbnail(QPixmap* aPix, int anIndex)
    :QLabel()
{

    this->setPixmap((*aPix).scaledToHeight(100));
    this->index = anIndex;
}

Thumbnail::~Thumbnail()
{

}

void Thumbnail::mousePressEvent(QMouseEvent *e)
{
    this->setStyleSheet("border:3px solid black;");
    emit clicked(this->index);
}

void Thumbnail::deselect()
{
    this->setStyleSheet("border:none");
}
