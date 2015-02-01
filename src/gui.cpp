#include "gui.h"
#include "ui_gui.h"

Gui::Gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gui)
{
    this->setFixedSize(800,600);
    ui->setupUi(this);
    QGridLayout* layout = new QGridLayout();

    //////////////////////
    // Video Management //
    //////////////////////

    /*QVideoWidget* video = new QVideoWidget();
    QMediaPlayer* mediaPlayer = new QMediaPlayer();
    mediaPlayer->setVideoOutput(video);
    layout->addWidget(video);
    mediaPlayer->setMedia(QMediaContent(QUrl::fromLocalFile(QFileInfo("Generique.mpeg").absoluteFilePath())));
    video->show();
    mediaPlayer->play();*/

    ////////////////////////
    // Drawing management //
    ////////////////////////

    this->drawings = new QList<QPoint*>();

    this->setLayout(layout);
}

Gui::~Gui()
{
    delete ui;
}

void Gui::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    for(int i=0;i<this->drawings->length();i++)
    {
        QPoint *q = this->drawings->at(i);
        painter.drawEllipse(q->x(),q->y(),20,20);
    }
}

void Gui::mousePressEvent(QMouseEvent *event)
{
    this->mouseDown=true;
}

void Gui::mouseReleaseEvent(QMouseEvent *event)
{
    this->mouseDown=false;
}

void Gui::mouseMoveEvent(QMouseEvent *event)
{
    if(this->mouseDown)
    {
        this->drawings->push_back(new QPoint(event->x(),event->y()));
        this->repaint();
    }
}
