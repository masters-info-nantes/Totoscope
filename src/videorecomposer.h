#ifndef VIDEORECOMPOSER_H
#define VIDEORECOMPOSER_H

#include <QObject>
#include <QProcess>

class VideoRecomposer : public QObject
{
    Q_OBJECT
    int framerate;
    QString video;
    QString path;
    QProcess* process;
public:
    explicit VideoRecomposer(QString, QString, int);
    ~VideoRecomposer();
    void startProcessing();
signals:
    void processingFinished();
public slots:

    void handleCommandEnd();
};

#endif // VIDEORECOMPOSER_H
