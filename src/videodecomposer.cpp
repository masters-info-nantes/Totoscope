#include "videodecomposer.h"

VideoDecomposer::VideoDecomposer(QString vid,int rate) :
    QObject(0)
{
    this->framerate = rate;
    this->process = new QProcess();
    this->video= vid;
}

void VideoDecomposer::startProcessing()
{
    qDebug("Clearing the temp folder");
    //Clear the folder
    QDir dir ("temp");

    QList<QFileInfo> infList = dir.entryInfoList();
    foreach(QFileInfo finfo, infList )
    {
        qDebug("file: "+ finfo.fileName().toUtf8()+" deleted");
        if(!dir.remove(finfo.fileName()))
        {
            qDebug("delete not possible");
        }
    }

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
