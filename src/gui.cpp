#include "gui.h"
#include "ui_gui.h"

Gui::Gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gui)
{
    this->setFixedSize(800,600);
    ui->setupUi(this);
    this->controller = new Controller();
    QGridLayout* layout = new QGridLayout();
    QStackedLayout* stack = new QStackedLayout();
    QWidget* container = new QWidget();
    this->drawingZone = new DrawingZone();

    ////////////////////////
    // Drawing management //
    ////////////////////////


    this->setLayout(layout);
    layout->addWidget(container);
    container->setLayout(stack);
    QLabel* frameWidget = new QLabel();
    frameWidget->setPixmap(QPixmap("videofolder/videoframe29.jpg"));
    stack->addWidget(frameWidget);
    stack->addWidget(drawingZone);
    stack->setCurrentWidget(drawingZone);
    stack->setStackingMode(QStackedLayout::StackAll);
}

Gui::~Gui()
{
    delete ui;
}

