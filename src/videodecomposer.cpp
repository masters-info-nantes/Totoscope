#include "videodecomposer.h"

VideoDecomposer::VideoDecomposer(QString vid,int rate) :
    QObject(0)
{
    this->index = 1;
    this->framerate = rate;
    this->process = new QProcess();
    this->video= vid;
}

void VideoDecomposer::startProcessing()
{
    QString command = "avconv -i "+this->video+" -vsync 1 -r "+QString::number(this->framerate)+" -y temp/movie%d.jpg";
    this->process->start(command);
    qDebug("Processing started...");
    QObject::connect(process,SIGNAL(finished(int)),this,SLOT(handleCommandEnd()));
}

void VideoDecomposer::handleCommandEnd()
{
    qDebug("Processing finished!");
    emit(this->processingFinished());
}
