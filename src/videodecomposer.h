#ifndef VIDEODECOMPOSER_H
#define VIDEODECOMPOSER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QUrl>
#include <QDir>

class VideoDecomposer : public QObject
{
    Q_OBJECT

    int framerate;
    QString video;
    QProcess* process;
public:
    explicit VideoDecomposer(QString,int);
    void startProcessing();
signals:
    void processingFinished();
public slots:

    void handleCommandEnd();

};

#endif // VIDEODECOMPOSER_H
