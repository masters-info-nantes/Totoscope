#include "project.h"

Project::Project(QString aName, QString aVideofile, int aFramerate)
{
    this->path="";
    this->name = aName;
    this->framerate = aFramerate;
    qDebug("project created");
    qDebug(aName.toUtf8());
    qDebug(aVideofile.toUtf8());
    qDebug(QString::number(aFramerate).toUtf8());
    this->drawings = new QList<QImage*>();
    this->pictures = new QList<QPixmap*>();
    // Décompose la vidéo en images
    this->decomposer = new VideoDecomposer(aVideofile,aFramerate);
    decomposer->startProcessing();
    QObject::connect(this->decomposer,SIGNAL(processingFinished()),this,SLOT(handleProcessing()));
}

Project::Project(QString aPath)
{
    this->path = aPath;
    qDebug("project opened!");
}

void Project::save(QString aPath)
{
    qDebug("save under...");
    this->path = aPath;
    QFile file(aPath+"manifest.tots");
    qDebug((aPath+"manifest.tots").toUtf8());
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug("Cannot write file ");
    }

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("project");
    writer.writeStartElement("name");
    writer.writeCharacters(this->name);
    writer.writeEndElement(); // name
    writer.writeStartElement("path");
    writer.writeCharacters(this->path);
    writer.writeEndElement(); // path
    writer.writeStartElement("framerate");
    writer.writeCharacters(QString::number(this->framerate));
    writer.writeEndElement(); // framerate
    writer.writeEndElement(); // project
    writer.writeEndDocument();

    this->save();

}

void Project::save()
{
    // Saving all the drawings
    QDir dir(this->path+"drawings/");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    QDir dir2(this->path+"pictures/");
    if (!dir2.exists()) {
        dir2.mkpath(".");
    }
    for(int i=0; i<this->drawings->length();i++)
    {
        this->drawings->at(i)->save(this->path+"drawings/"+QString::number(i)+".png","PNG");
        this->pictures->at(i)->save(this->path+"pictures/"+QString::number(i)+".jpg","JPG");
    }

}

Project::~Project()
{

}

void Project::handleProcessing()
{
    QDir dir("temp");
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();
    int i;
    for (i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        QPixmap* pix = new QPixmap(fileInfo.absoluteFilePath());
        this->pictures->push_back(pix);
        this->drawings->push_back(new QImage(pix->width(),pix->height(),QImage::Format_ARGB32));
    }
    qDebug(QString::number(i).toUtf8()+" images generated");
    emit(this->projectCreated());
}

QList<QImage*>* Project::getDrawings()
{
    return this->drawings;
}

QList<QPixmap*>* Project::getPictures()
{
    return this->pictures;
}

QString Project::getPath()
{
    return this->path;
}
