#include "exportgui.h"

ExportGui::ExportGui(int i, Controller* aController)
    : QWidget(0)
{
    this->setWindowTitle(tr("Exporter..."));
    this->controller=aController;
    dirEdit = new QLineEdit();
    dirEditVideo = new QLineEdit();
    browse = new QPushButton("Parcourir");
    QObject::connect(this->browse,SIGNAL(clicked()),this,SLOT(browseImg()));

    browseVideo = new QPushButton("Parcourir");
        QObject::connect(this->browseVideo,SIGNAL(clicked()),this,SLOT(browseVid()));
    codecBox = new QComboBox;
        codecBox->addItem("h264");
    vidEdit = new QLineEdit();
    formatBox = new QComboBox;
        formatBox->addItem(".jpg");
        formatBox->addItem(".png");
    QPushButton *cancelButton = new QPushButton("Annuler");
    QObject::connect(cancelButton,SIGNAL(clicked()),this,SLOT(close()));
    QPushButton *exportButton = new QPushButton("Exporter");
    QObject::connect(exportButton,SIGNAL(clicked()),this,SLOT(exportVideo()));

    QWidget *vidPage = new QWidget;
        QGridLayout *vidLayout = new QGridLayout;
            vidLayout->addWidget(new QLabel("Emplacement :"),0,0);
            vidLayout->addWidget(dirEditVideo,1,0);
            vidLayout->addWidget(browseVideo,1,1);
            vidLayout->addWidget(new QLabel("Codec :"),2,0);
            vidLayout->addWidget(codecBox,3,0);
            vidLayout->addWidget(new QLabel("Nom de la vidéo :"),4,0);
            vidLayout->addWidget(vidEdit,5,0);
        vidPage->setLayout(vidLayout);

    QWidget *imgPage = new QWidget;
        QGridLayout *imgLayout = new QGridLayout;
            imgLayout->addWidget(new QLabel("Emplacement :"),0,0);
            imgLayout->addWidget(dirEdit,1,0);
            imgLayout->addWidget(browse,1,1);
            imgLayout->addWidget(new QLabel("Format :"),2,0);
            imgLayout->addWidget(formatBox,3,0);
        imgPage->setLayout(imgLayout);

    QTabWidget *tabWidget = new QTabWidget;
        tabWidget->addTab(imgPage, "Image");
        tabWidget->addTab(vidPage, "Vidéo");
        tabWidget->setCurrentIndex(i);

    QGridLayout *layout = new QGridLayout;
        layout->addWidget(tabWidget,0,0,1,3);
        layout->addWidget(cancelButton,1,1);
        layout->addWidget(exportButton,1,2);
    this->setLayout(layout);
}

ExportGui::~ExportGui()
{

}

void ExportGui::exportVideo()
{
    this->controller->exportVideo(this->dirEditVideo->text());
}

void ExportGui::browseImg()
{
    this->dirEdit->setText(QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
}

void ExportGui::browseVid()
{
        this->dirEditVideo->setText(QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
}

void ExportGui::exportImg()
{
        this->controller->exportImages(this->dirEdit->text()+"/");
}
