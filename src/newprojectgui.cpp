#include "newprojectgui.h"

NewProjectGui::NewProjectGui(Controller* aController) :
    QWidget(0),controller(aController)
{
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    this->setWindowTitle("Nouveau Projet");
    this->setStyleSheet("background:#2c3e50;color:white;");
    layout = new QGridLayout();
    nameEdit = new QLineEdit();
    nameEdit->setMinimumWidth(400);
    error = new QLabel();
    videoButton = new QPushButton("Parcourir");
    this->videoButton->setStyleSheet("background:#34495e;border-radius:3px;padding:5%;color:white;");
    this->videoButton->setMinimumSize(100,30);
    QObject::connect(videoButton,SIGNAL(clicked()),this,SLOT(chooseVideo()));
    selectFramerate = new QComboBox();
    selectFramerate->addItem("6");
    selectFramerate->addItem("8");
    selectFramerate->addItem("12");
    selectFramerate->addItem("16");
    videoEdit = new QLineEdit();
    createButton = new QPushButton("Création de Projet");
    this->createButton->setMinimumSize(100,30);
    this->createButton->setStyleSheet("background:#34495e;border-radius:3px;padding:5%;color:white;");
    QObject::connect(createButton,SIGNAL(clicked()),this,SLOT(createProject()));
    this->layout->addWidget(new QLabel("Nom du projet:"),0,0);
    this->layout->addWidget(nameEdit,1,0);
    this->layout->addWidget(new QLabel("Vidéo:"),2,0);
    this->layout->addWidget(videoEdit,3,0);
    this->layout->addWidget(videoButton,3,1);
    this->layout->addWidget(new QLabel("FrameRate:"),4,0);
    this->layout->addWidget(selectFramerate,5,0);
    this->layout->addWidget(error,6,0,1,2);
    this->layout->addWidget(createButton,7,2);
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
    QFile* check = new QFile(this->videoEdit->text());
    if(this->nameEdit->text()=="")
        this->error->setText("Votre projet doit avoir un nom!");
    else if(!check->exists())
        this->error->setText("Le fichier n'existe pas!");
    else
    {
        this->controller->createProject(this->nameEdit->text(),this->videoEdit->text(),this->selectFramerate->currentText().toInt());
        QObject::connect(this->controller,SIGNAL(projectCreated()),this,SLOT(nextWindow()));
    }
}

void NewProjectGui::nextWindow()
{

    Gui* window = new Gui(this->controller);
    window->show();
    this->close();
}
