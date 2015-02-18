#include "newprojectgui.h"

NewProjectGui::NewProjectGui(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout();
    nameEdit = new QLineEdit();
    nameEdit->setMinimumWidth(400);
    videoButton = new QPushButton("Browse");
    QObject::connect(videoButton,SIGNAL(clicked()),this,SLOT(chooseVideo()));
    selectFramerate = new QComboBox();
    selectFramerate->addItem("6");
    selectFramerate->addItem("8");
    selectFramerate->addItem("12");
    selectFramerate->addItem("16");
    videoEdit = new QLineEdit();
    createButton = new QPushButton("Create Project");
    QObject::connect(createButton,SIGNAL(clicked()),this,SLOT(createProject()));
    this->layout->addWidget(new QLabel("Nom du projet:"),0,0);
    this->layout->addWidget(nameEdit,1,0);
    this->layout->addWidget(new QLabel("Vidéo:"),2,0);
    this->layout->addWidget(videoEdit,3,0);
    this->layout->addWidget(videoButton,3,1);
    this->layout->addWidget(new QLabel("FrameRate:"),4,0);
    this->layout->addWidget(selectFramerate,5,0);
    this->layout->addWidget(createButton,6,2);
    this->setLayout(layout);
}

NewProjectGui::~NewProjectGui()
{

}

void NewProjectGui::chooseVideo()
{
    QFileDialog* dialog = new QFileDialog();
    videoEdit->setText(dialog->getOpenFileName(this,"Open Video", "/home/","All files (*.*)"));
}

void NewProjectGui::createProject()
{
    Gui* window = new Gui();
    window->show();
    this->close();
}
