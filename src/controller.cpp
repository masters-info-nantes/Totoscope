#include "controller.h"

Controller::Controller()
    :QObject()
{
    this->currentImageIndex = 0;
}

void Controller::openProject(QString path)
{
    this->project = new Project(path);
     //QObject::connect(this->project,SIGNAL(projectCreated()),this,SLOT(handleProjectCreation()));
}

void Controller::createProject(QString aName, QString aVideofile, int aFramerate)
{
    this->project = new Project(aName,aVideofile,aFramerate);
    QObject::connect(this->project,SIGNAL(projectCreated()),this,SLOT(handleProjectCreation()));
}

void Controller::saveProject()
{
    this->project->save();
}

void Controller::saveProject(QString aPath)
{
    this->project->save(aPath);
}

void Controller::handleProjectCreation()
{
    emit(this->projectCreated());
}

QPixmap* Controller::getPicture()
{
    return this->project->getPictures()->at(this->currentImageIndex);
}

void Controller::setFrame(int index)
{
    this->currentImageIndex = index;
}

QImage* Controller::getDrawing()
{
    return this->project->getDrawings()->at(this->currentImageIndex);
}

QList<QImage*>* Controller::getOnions(int number)
{
    QList<QImage*>* onion = new QList<QImage*>();
    for(int i=this->currentImageIndex-1;i>=0&&i>(this->currentImageIndex-number-1);i--)
    {
        onion->push_back(this->project->getDrawings()->at(i));
    }
    return onion;
}

void Controller::nextFrame()
{
    if(this->currentImageIndex<this->project->getPictures()->length()-1)
    this->currentImageIndex++;
}

void Controller::previousFrame()
{
    if(this->currentImageIndex>0)
    this->currentImageIndex--;
}

bool Controller::isProjectSaved()
{
    if(this->project->getPath()=="")
        return false;
    return true;
}

void Controller::exportVideo(QString aPath)
{
    qDebug("Exporting...");
    qDebug(this->project->getPath().toUtf8());
    this->project->exportVideo(aPath);
}

QList<QPixmap*>* Controller::getPictures()
{
    return this->project->getPictures();
}
