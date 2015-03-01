#include "videorecomposer.h"

VideoRecomposer::VideoRecomposer(QString vid,QString aPath,int rate)
    : QObject(0)
{
    this->path = aPath;
    this->framerate = rate;
    this->process = new QProcess();
    this->video= vid;
}

void VideoRecomposer::startProcessing()
{
    QString command = "avconv -i "+this->path+"/drawings/%d.png -b:v 1000k -r "+QString::number(this->framerate)+" -y "+this->video+"/movie.mp4";
    qDebug("Command: "+command.toUtf8());
    this->process->start(command);
    qDebug("Processing started...");
    QObject::connect(process,SIGNAL(finished(int)),this,SLOT(handleCommandEnd()));
}

void VideoRecomposer::handleCommandEnd()
{
    qDebug("Processing finished!");
    emit(this->processingFinished());
}
VideoRecomposer::~VideoRecomposer()
{

}

