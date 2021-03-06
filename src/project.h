#ifndef PROJECT_H
#define PROJECT_H

#include <QList>
#include <QImage>
#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <videodecomposer.h>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QPixmap>
#include <QObject>
#include <QMessageBox>
#include <videorecomposer.h>

class Project : public QObject
{

    Q_OBJECT

    VideoDecomposer* decomposer;
    QString name;
    QString path;
    int framerate;
    QList<QImage*>* drawings;
    QList<QPixmap*>* pictures;
public:
    Project(QString aName, QString aVideofile, int aFramerate);
    Project(QString aPath);
    void save(QString aPath);
    void save();
    void exportVideo(QString);
    void exportImages(QString);
    QList<QImage*>* getDrawings();
    QList<QPixmap*>* getPictures();
    QString getPath();
    ~Project();
signals:
    void projectCreated();
    void projectLoaded();
public slots:

    void handleProcessing();

};

#endif // PROJECT_H
