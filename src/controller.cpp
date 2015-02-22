#include "controller.h"

Controller::Controller()
    :QObject()
{
    this->decomposer = new VideoDecomposer("Generique.MOV",8);
    //decomposer->startProcessing();

}

void Controller::openProject(QString path)
{
    this->project = new Project(path);
}

void Controller::createProject(QString aName, QString aVideofile, int aFramerate)
{
    this->project = new Project(aName,aVideofile,aFramerate);
}

void Controller::saveProject()
{
    this->project->save();
}

void Controller::saveProject(QString aPath)
{
    this->project->save(aPath);
}
