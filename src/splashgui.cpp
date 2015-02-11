#include "splashgui.h"

SplashGui::SplashGui() :
    QWidget(0)
{
    this->setFixedSize(600,400);
    this->layout= new QGridLayout();
    this->newProject = new QPushButton("New");
    this->openProject = new QPushButton("Open");
    this->quit = new QPushButton("Quit");
    this->title = new QLabel("Totoscope!");
    this->description = new QLabel("Developed by Marie Lenogue and Nicolas Brondin");
    this->setLayout(this->layout);
    this->layout->addWidget(this->title,0,0,1,3);
    this->layout->addWidget(this->description,1,0,1,3);
    this->layout->addWidget(this->newProject,2,0);
    this->layout->addWidget(this->openProject,2,1);
    this->layout->addWidget(this->quit,2,2);
    QObject::connect(this->openProject,SIGNAL(clicked()),this,SLOT(windowfile()));
    QObject::connect(this->newProject,SIGNAL(clicked()),this,SLOT(createproject()));
}

void SplashGui::windowfile()
{
    QFileDialog*  file= new QFileDialog();
    QString project = file->getOpenFileName(this,"Open Project", "/","Totoscope Project (*.tts)");

}

void SplashGui::createproject()
{
    this->close();
    NewProjectGui* win = new NewProjectGui();
    win->show();
}
