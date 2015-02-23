#include "project.h"

Project::Project(QString aName, QString aVideofile, int aFramerate)
{
    this->path="";
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

}

void Project::save()
{
    // Creating Project File
    qDebug("save");
    QFile file("tto.xml");
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            qDebug("Cannot write file ");
        }

    QXmlStreamWriter writer(&file);
    // use QXmlStreamWriter class to generate the XML
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("html");
    writer.writeStartElement("a");
    writer.writeAttribute("href", "http://example.com/");
    writer.writeCharacters("My wonderful link");
    writer.writeEndElement(); // a
    writer.writeEndElement(); // html
    writer.writeEndDocument();

    // Saving all the drawings
    for(int i=0; i<this->drawings->length();i++)
    {
        this->drawings->at(i)->save(QString::number(i)+".png","PNG");
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
        QPixmap* pix = new QPixmap(fileInfo.fileName());
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

