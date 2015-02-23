#include "controller.h"

Controller::Controller()
    :QObject()
{

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
