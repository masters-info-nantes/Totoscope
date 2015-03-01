#include "splashgui.h"

SplashGui::SplashGui(Controller* aController) :
    QWidget(0),controller(aController)
{
    //this->setFixedSize(600,400);
    this->setMinimumSize(600,200);
    this->setStyleSheet("background:#545454;color:white;");
    this->layout= new QGridLayout();
    this->newProject = new QPushButton("Nouveau");
        this->newProject->setIcon(QIcon("../src/pictures/new.png"));
        this->newProject->setIconSize(QSize(32,32));
        this->newProject->setStyleSheet("background:#3a3a3a;border-radius:3px;padding:5%;");
    this->openProject = new QPushButton("Ouvrir");
        this->openProject->setIcon(QIcon("../src/pictures/open.png"));
        this->openProject->setIconSize(QSize(32,32));
        this->openProject->setStyleSheet("background:#3a3a3a;border-radius:3px;padding:5%;");
    this->quit = new QPushButton("Fermer");
        this->quit->setIcon(QIcon("../src/pictures/exit.png"));
        this->quit->setIconSize(QSize(32,32));
        this->quit->setStyleSheet("background:#3a3a3a;border-radius:3px;padding:5%;");
    this->title = new QLabel("Totoscope!");
    this->title->setStyleSheet("color:#3a3a3a;");
    this->title->setAlignment(Qt::AlignCenter);
    this->title->setFont(QFont("Arial",40));
    this->description = new QLabel("Developed by Marie Lenogue and Nicolas Brondin");
    this->setLayout(this->layout);
    this->layout->addWidget(this->title,0,0,1,3);
    this->layout->addWidget(this->description,1,0,1,3);
    this->layout->addWidget(this->newProject,2,0);
    this->layout->addWidget(this->openProject,2,1);
    this->layout->addWidget(this->quit,2,2);
    QObject::connect(this->openProject,SIGNAL(clicked()),this,SLOT(windowfile()));
    QObject::connect(this->newProject,SIGNAL(clicked()),this,SLOT(createproject()));
    QObject::connect(this->quit,SIGNAL(clicked()),this,SLOT(close()));
}

void SplashGui::windowfile()
{
    QFileDialog*  file= new QFileDialog();
    QString project = file->getOpenFileName(this,"Open Project", "/home","");
    qDebug(project.toUtf8());
    if(project!="")
    {
        this->controller->openProject(project);

        Gui* win = new Gui(this->controller);
        win->show();
         this->close();
    }

}

void SplashGui::createproject()
{
    this->close();
    NewProjectGui* win = new NewProjectGui(this->controller);
    win->show();
}
