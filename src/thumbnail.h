#ifndef THUMBNAIL_H
#define THUMBNAIL_H

#include <QLabel>
#include <QPixmap>
#include <QtDebug>

class Thumbnail : public QLabel
{
    Q_OBJECT
    QString path;

public:
    explicit Thumbnail(QImage, QString filepath, QWidget *parent = 0);
    Thumbnail(QPixmap, QString filepath, QWidget *parent = 0);
    Thumbnail(QString, QWidget *parent = 0);
    ~Thumbnail();
    QString getPath();

signals:
    void clicked(QString);

public slots:
    void mousePressEvent(QMouseEvent *e);

};

#endif // THUMBNAIL_H
