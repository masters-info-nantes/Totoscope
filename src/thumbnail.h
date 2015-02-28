#ifndef THUMBNAIL_H
#define THUMBNAIL_H

#include <QLabel>
#include <QPixmap>
#include <QtDebug>

class Thumbnail : public QLabel
{
    Q_OBJECT
    QPixmap* pix;
    int index;

public:

    Thumbnail(QPixmap*, int);
    ~Thumbnail();
    void deselect();

signals:
    void clicked(int);

public slots:
    void mousePressEvent(QMouseEvent *e);

};

#endif // THUMBNAIL_H
