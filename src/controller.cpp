#include "controller.h"

Controller::Controller()
    :QObject()
{
    this->currentImageIndex = 30;
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

QImage* Controller::getDrawing()
{
    return this->project->getDrawings()->at(this->currentImageIndex);
}

QList<QImage*>* Controller::getOnions(int number)
{
    QList<QImage*>* onion = new QList<QImage*>();
    for(int i=this->currentImageIndex;i>0&&i>(this->currentImageIndex-number);i--)
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
    this->project->exportVideo(aPath);
}
