#include "gui.h"
#include "ui_gui.h"

Gui::Gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gui)
{
    this->setFixedSize(800,600);
    ui->setupUi(this);
    QGridLayout* layout = new QGridLayout();
    this->index = 1;
    this->framerate = 8;
    this->list = new QList<QVideoFrame>();

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

    /////////////////////////////
    // Frame per Frame storage //
    /////////////////////////////

    /*QVideoProbe *probe = new QVideoProbe;
    connect(probe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(processFrame(QVideoFrame)));
    probe->setSource(mediaPlayer); // Returns true, hopefully.*/

    ////////////////////////
    // Drawing management //
    ////////////////////////

    this->drawings = new QList<QPoint*>();
    this->image=new QImage(800,600,QImage::Format_ARGB32_Premultiplied);
    this->prev_pos = QPoint(-666,-666);
    this->setLayout(layout);
}

Gui::~Gui()
{
    delete ui;
}
/*
void Gui::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    QPen pen = QPen(Qt::black);
    pen.setWidth(20);
    painter.setPen(pen);
    for(int i=0;i<this->drawings->length();i++)
    {
        QPoint *q = this->drawings->at(i);
        //painter.drawEllipse(q->x(),q->y(),20,20);
        if(i>0)
        {
            QPoint *qbefore = this->drawings->at(i-1);
            painter.drawLine(q->x(),q->y(),qbefore->x(),qbefore->y());
        }

    }
}*/

void Gui::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawImage(0,0,*(this->image));
}

void Gui::processFrame(QVideoFrame frame)
{
    if(this->index%framerate==0)
    {
        qDebug()<<this->index;
        this->list->push_back(frame);
    }
    this->index++;
}

void Gui::mousePressEvent(QMouseEvent *event)
{
    this->mouseDown=true;
}

void Gui::mouseReleaseEvent(QMouseEvent *event)
{
    this->mouseDown=false;
    this->prev_pos = QPoint(-666,-666);
}

/*void Gui::mouseMoveEvent(QMouseEvent *event)
{
    if(this->mouseDown)
    {
        this->drawings->push_back(new QPoint(event->x(),event->y()));
        this->update();
    }
}*/

void Gui::mouseMoveEvent(QMouseEvent *event)
{
    if(this->mouseDown&&this->prev_pos.x()!=-666&&this->prev_pos.y()!=-666)
    {
        QPainter painter(this->image);
        painter.setPen(Qt::black);
        painter.drawLine(this->prev_pos,event->pos());
        update();
    }
    this->prev_pos = event->pos();
}
