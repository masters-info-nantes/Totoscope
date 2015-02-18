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
    //int i;

    ////////////////////////////
    /// Barre Menu principal ///
    ////////////////////////////
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu;
        fileMenu = menuBar->addMenu(tr("&Fichier"));
        QAction *newAct = new QAction(this);
            newAct = fileMenu->addAction("Nouveau Projet");
        QAction *openAct = new QAction(this);
            openAct = fileMenu->addAction("Ouvrir Projet");
        QAction *saveAct = new QAction(this);
            saveAct = fileMenu->addAction("Enregistrer");
        QAction *saveAsAct = new QAction(this);
            saveAsAct = fileMenu->addAction("Enregistrer sous");
        QMenu *exportMenu = new QMenu;
            exportMenu = fileMenu->addMenu("Exporter...");
            QAction *imgExpAct = new QAction(this);
                imgExpAct = exportMenu->addAction("au format image");
            QAction *vidExpAct = new QAction(this);
                vidExpAct = exportMenu->addAction("au format vidéo");
        QAction *closeAct = new QAction(this);
            closeAct = fileMenu->addAction("Fermer Projet");
        QAction *exitAct = new QAction(this);
            exitAct = fileMenu->addAction("Quitter");
    QMenu *editMenu = new QMenu;
        editMenu = menuBar->addMenu(tr("&Edition"));
        QAction *undoAct = new QAction(this);
            undoAct = editMenu->addAction("Annuler");
        QAction *redoAct = new QAction(this);
            redoAct = editMenu->addAction("Retablir");
        QAction *ognionAct = new QAction(this);
            ognionAct = editMenu->addAction("Pelures d'Oignon");
            ognionAct->setCheckable(true);
        QAction *vidAct = new QAction(this);
            vidAct = editMenu->addAction("Vidéo");
            vidAct->setCheckable(true);
            vidAct->setChecked(true);
        QAction *playAct = new QAction(this);
            playAct = editMenu->addAction("Lecture/Pause");
        QAction *stopAct = new QAction(this);
            stopAct = editMenu->addAction("Stop");
        QAction *nextAct = new QAction(this);
            nextAct = editMenu->addAction("Next");
    QMenu *helpMenu = new QMenu;
        helpMenu = menuBar->addMenu(tr("&Aide"));
        QAction *aboutAct = new QAction(this);
            aboutAct = helpMenu->addAction("A Propos");

    //////////////////////////////
    /// Barre verticale gauche ///
    //////////////////////////////
    QPushButton *penButton = new QPushButton;
        penButton->setIcon(QIcon("../src/pictures/pen.png"));
        penButton->setIconSize(QSize(32,32));
    QSpinBox *sizePen = new QSpinBox;
        sizePen->setRange(1,50);
        //QObject::connect(sizePen, SIGNAL(valueChanged(i)), this, SLOT(setPenSize(i)));
    QPushButton *eraserButton = new QPushButton;
        eraserButton->setIcon(QIcon("../src/pictures/eraser.png"));
        eraserButton->setIconSize(QSize(32,32));
    this->colorButton = new QPushButton;
        QObject::connect(colorButton, SIGNAL(clicked()), this, SLOT(showPicker()));
    QPushButton *backButton = new QPushButton;
        backButton->setIcon(QIcon("../src/pictures/back.png"));
        backButton->setIconSize(QSize(32,32));
    QVBoxLayout *vbox = new QVBoxLayout;
        vbox->addWidget(penButton);
        vbox->addWidget(sizePen);
        vbox->addWidget(eraserButton);
        vbox->addWidget(colorButton);
        vbox->addWidget(backButton);


    /////////////////////////
    /// Drawing management //
    /////////////////////////
    this->setLayout(layout);
    layout->addWidget(menuBar,0,0);
    layout->addLayout(vbox,1,0);
    layout->addWidget(container,1,1);
    container->setLayout(stack);
    QLabel* frameWidget = new QLabel();
    frameWidget->setPixmap(QPixmap("videofolder/videoframe29.jpg"));
    stack->addWidget(frameWidget);
    stack->addWidget(drawingZone);
    stack->setCurrentWidget(drawingZone);
    stack->setStackingMode(QStackedLayout::StackAll);
}

void Gui::showPicker()
{
    this->colorPalette = new QColorDialog();
    colorPalette->show();
    QColor color =  colorPalette->selectedColor();
    QPixmap pixmap(65,65);
    pixmap.fill(color);
    colorButton->setIcon(QIcon(pixmap));

}

Gui::~Gui()
{
    delete ui;
}

