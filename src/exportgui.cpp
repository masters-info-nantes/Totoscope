#include "exportgui.h"

ExportGui::ExportGui(int i, QWidget *parent) : QWidget(parent)
{

    dirEdit = new QLineEdit();
    browse = new QPushButton("Parcourir");
    codecBox = new QComboBox;
        codecBox->addItem("h264");
    vidEdit = new QLineEdit();
    formatBox = new QComboBox;
        formatBox->addItem(".jpg");
        formatBox->addItem(".png");
    QPushButton *cancelButton = new QPushButton("Annuler");
    QPushButton *exportButton = new QPushButton("Exporter");

    QWidget *vidPage = new QWidget;
        QGridLayout *vidLayout = new QGridLayout;
            vidLayout->addWidget(new QLabel("Emplacement :"),0,0);
            vidLayout->addWidget(dirEdit,1,0);
            vidLayout->addWidget(browse,1,1);
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