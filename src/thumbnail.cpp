#include "thumbnail.h"


Thumbnail::Thumbnail(QString filepath, int anIndex)
    :QLabel()
{
    this->setPixmap(QPixmap::fromImage(QImage(filepath)));
    this->path = filepath;
    this->index = anIndex;
}

Thumbnail::~Thumbnail()
{

}

QString Thumbnail::getPath()
{
    return this->path;
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
