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

    ////////////////////////////
    /// Barre Menu principal ///
    ////////////////////////////
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu;
        fileMenu = menuBar->addMenu(tr("&Fichier"));
        QAction *newAct = new QAction(this);
            newAct = fileMenu->addAction("Nouveau Projet");
            newAct->setShortcut(QKeySequence::New);
        QAction *openAct = new QAction(this);
            openAct = fileMenu->addAction("Ouvrir Projet");
            openAct->setShortcut(QKeySequence::Open);
        fileMenu->addSeparator();
        QAction *saveAct = new QAction(this);
            saveAct = fileMenu->addAction("Enregistrer");
            saveAct->setShortcut(QKeySequence::Save);
        QAction *saveAsAct = new QAction(this);
            saveAsAct = fileMenu->addAction("Enregistrer sous");
            saveAsAct->setShortcut(QKeySequence::SaveAs);
        fileMenu->addSeparator();
        QMenu *exportMenu = new QMenu;
            exportMenu = fileMenu->addMenu("Exporter...");
            //raccourci impossible sur menu?
            QAction *imgExpAct = new QAction(this);
                imgExpAct = exportMenu->addAction("au format image");
            QAction *vidExpAct = new QAction(this);
                vidExpAct = exportMenu->addAction("au format vidéo");
        fileMenu->addSeparator();
        QAction *closeAct = new QAction(this);
            closeAct = fileMenu->addAction("Fermer Projet");
            closeAct->setShortcut(QKeySequence::Close);
        QAction *exitAct = new QAction(this);
            exitAct = fileMenu->addAction("Quitter");
            exitAct->setShortcut(QKeySequence::Quit);

    QMenu *editMenu = new QMenu;
        editMenu = menuBar->addMenu(tr("&Edition"));
        QAction *undoAct = new QAction(this);
            undoAct = editMenu->addAction("Annuler");
            undoAct->setShortcut(QKeySequence::Undo);
        QAction *redoAct = new QAction(this);
            redoAct = editMenu->addAction("Retablir");
            redoAct->setShortcut(QKeySequence::Redo);
        editMenu->addSeparator();
        QAction *ognionAct = new QAction(this);
            ognionAct = editMenu->addAction("Pelures d'Oignon");
            ognionAct->setCheckable(true);
        QAction *vidAct = new QAction(this);
            vidAct = editMenu->addAction("Vidéo");
            vidAct->setCheckable(true);
            vidAct->setChecked(true);
        editMenu->addSeparator();
        QAction *playAct = new QAction(this);
            playAct = editMenu->addAction("Lecture/Pause");
            playAct->setShortcut(QKeySequence(Qt::Key_Space));
        QAction *stopAct = new QAction(this);
            stopAct = editMenu->addAction("Stop");
            stopAct->setShortcut(QKeySequence(Qt::Key_Left));
        QAction *nextAct = new QAction(this);
            nextAct = editMenu->addAction("Next");
            nextAct->setShortcut(QKeySequence(Qt::Key_Right));

        QMenu *helpMenu = new QMenu;
        helpMenu = menuBar->addMenu(tr("&Aide"));
        QAction *aboutAct = new QAction(this);
            aboutAct = helpMenu->addAction("A Propos");

    //////////////////////////////
    /// Barre horizontale haut ///
    //////////////////////////////
    QToolBar *topBar = new QToolBar(this);
        QAction *stopButton = new QAction(this);
            stopButton = topBar->addAction(QIcon("../src/pictures/stop.png"),"Stop");
        this->playButton = new QAction(this);
            playButton = topBar->addAction(QIcon("../src/pictures/play.png"),"Play");
            QObject::connect(playButton, SIGNAL(triggered()), this, SLOT(playDraw()));
        this->pauseButton = new QAction(this);
            pauseButton = topBar->addAction(QIcon("../src/pictures/pause.png"),"Pause");
            pauseButton->setVisible(false);
            QObject::connect(pauseButton, SIGNAL(triggered()), this, SLOT(pauseDraw()));
        QAction *nextButton = new QAction(this);
            nextButton = topBar->addAction(QIcon("../src/pictures/next.png"),"Next");
        topBar->addSeparator();
        QAction *oignonButton = new QAction(this);
            QCheckBox *oignonCheck = new QCheckBox("Pelures d'Oignon");
            oignonButton = topBar->addWidget(oignonCheck);
        QAction *nbOignon = new QAction(this);
            QSpinBox *oignonSpin = new QSpinBox;
                oignonSpin->setRange(1,5);
            nbOignon = topBar->addWidget(oignonSpin);
        QAction *vidButton = new QAction(this);
            QCheckBox *vidCheck = new QCheckBox("Vidéo");
            vidButton = topBar->addWidget(vidCheck);

    //////////////////////////////
    /// Barre verticale gauche ///
    //////////////////////////////
    QToolBar *leftBar = new QToolBar(this);
        leftBar->setOrientation(Qt::Vertical);
        QAction *penButton = new QAction(this);
            penButton = leftBar->addAction(QIcon("../src/pictures/pen.png"),"Crayon");
        QAction *sizeButton = new QAction(this);
            QSpinBox *sizePen = new QSpinBox;
            sizePen->setRange(1,50);
            sizeButton = leftBar->addWidget(sizePen);
            QObject::connect(sizePen, SIGNAL(valueChanged(int)), this, SLOT(setPenSize(int)));
        QAction *eraserButton = new QAction(this);
            eraserButton = leftBar->addAction(QIcon("../src/pictures/eraser.png"),"Gomme");
        this->colorButton = new QAction(this);
            colorButton = leftBar->addAction("Couleur");
            QObject::connect(colorButton, SIGNAL(triggered()), this, SLOT(showPicker()));
        QAction *backButton = new QAction(this);
            backButton = leftBar->addAction(QIcon("../src/pictures/back.png"),"Annuler");

    /////////////////////////
    /// Drawing management //
    /////////////////////////
    this->setLayout(layout);
    layout->addWidget(menuBar);
    layout->addWidget(topBar,0,3);
    layout->addWidget(leftBar,1,0);
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

void Gui::setPenSize(int i)
{
    drawingZone->setPenSize(i);
}

void Gui::playDraw()
{
    //TODO jouer les dessins
    playButton->setVisible(false);
    pauseButton->setVisible(true);
}

void Gui::pauseDraw()
{
    //TODO pause sur la lecture des dessins
    playButton->setVisible(true);
    pauseButton->setVisible(false);
}

Gui::~Gui()
{
    delete ui;
}

