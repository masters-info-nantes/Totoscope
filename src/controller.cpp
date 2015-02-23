#include "controller.h"

Controller::Controller()
    :QObject()
{
    this->currentImageIndex = 30;
}

void Controller::openProject(QString path)
{
    this->project = new Project(path);
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

void Controller::nextFrame()
{
    this->currentImageIndex++;
}

void Controller::previousFrame()
{
    this->currentImageIndex--;
}
