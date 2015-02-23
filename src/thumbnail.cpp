#include "thumbnail.h"

Thumbnail::Thumbnail(QImage img, QString filepath, QWidget *parent) : QLabel(parent)
{
    this->setPixmap(QPixmap::fromImage(img));
    this->path = filepath;
}

Thumbnail::Thumbnail(QPixmap pix, QString filepath, QWidget *parent)
{
    this->setPixmap(pix);
    this->path = filepath;
}

Thumbnail::Thumbnail(QString filepath, QWidget *parent)
{
    this->setPixmap(QPixmap::fromImage(QImage(filepath)));
    this->path = filepath;
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
    emit clicked(this->path);
}
