#include "splashgui.h"

SplashGui::SplashGui(Controller* aController) :
    QWidget(0),controller(aController)
{
    this->setFixedSize(600,400);
    this->layout= new QGridLayout();
    this->newProject = new QPushButton("Nouveau");
        this->newProject->setIcon(QIcon("../src/pictures/new.png"));
        this->newProject->setIconSize(QSize(32,32));
    this->openProject = new QPushButton("Ouvrir");
        this->openProject->setIcon(QIcon("../src/pictures/open.png"));
        this->openProject->setIconSize(QSize(32,32));
    this->quit = new QPushButton("Fermer");
        this->quit->setIcon(QIcon("../src/pictures/exit.png"));
        this->quit->setIconSize(QSize(32,32));
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
    QString project = file->getOpenFileName(this,"Open Project", "/home","");
    qDebug(project.toUtf8());
    if(project!="")
    {
        this->controller->openProject(project);
        this->close();
        Gui* win = new Gui(this->controller);
        win->show();
    }

}

void SplashGui::createproject()
{
    this->close();
    NewProjectGui* win = new NewProjectGui(this->controller);
    win->show();
}
