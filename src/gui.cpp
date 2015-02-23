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
            QObject::connect(newAct, SIGNAL(triggered()), this, SLOT(newProject()));
        QAction *openAct = new QAction(this);
            openAct = fileMenu->addAction("Ouvrir Projet");
            openAct->setShortcut(QKeySequence::Open);
            QObject::connect(openAct, SIGNAL(triggered()), this, SLOT(openProject()));
        fileMenu->addSeparator();
        QAction *saveAct = new QAction(this);
            saveAct = fileMenu->addAction("Enregistrer");
            saveAct->setShortcut(QKeySequence::Save);
            QObject::connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));
        QAction *saveAsAct = new QAction(this);
            saveAsAct = fileMenu->addAction("Enregistrer sous");
            saveAsAct->setShortcut(QKeySequence::SaveAs);
            QObject::connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));
        fileMenu->addSeparator();
        QMenu *exportMenu = new QMenu;
            exportMenu = fileMenu->addMenu("Exporter...");
            //raccourci impossible sur menu?
            QAction *imgExpAct = new QAction(this);
                imgExpAct = exportMenu->addAction("au format image");
                QObject::connect(imgExpAct, SIGNAL(triggered()), this, SLOT(imgExport()));
            QAction *vidExpAct = new QAction(this);
                vidExpAct = exportMenu->addAction("au format vidéo");
                QObject::connect(vidExpAct, SIGNAL(triggered()), this, SLOT(vidExport()));
        fileMenu->addSeparator();
        QAction *closeAct = new QAction(this);
            closeAct = fileMenu->addAction("Fermer Projet");
            closeAct->setShortcut(QKeySequence::Close);
            QObject::connect(closeAct, SIGNAL(triggered()), this, SLOT(closeProject()));
        QAction *exitAct = new QAction(this);
            exitAct = fileMenu->addAction("Quitter");
            exitAct->setShortcut(QKeySequence::Quit);
            QObject::connect(exitAct, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));

    QMenu *editMenu = new QMenu;
        editMenu = menuBar->addMenu(tr("&Edition"));
        QAction *undoAct = new QAction(this);
            undoAct = editMenu->addAction("Annuler");
            undoAct->setShortcut(QKeySequence::Undo);
            QObject::connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));
        QAction *redoAct = new QAction(this);
            redoAct = editMenu->addAction("Retablir");
            redoAct->setShortcut(QKeySequence::Redo);
            QObject::connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));
        editMenu->addSeparator();
        QAction *oignionAct = new QAction(this);
            oignionAct = editMenu->addAction("Pelures d'Oignon");
            oignionAct->setCheckable(true);
            QObject::connect(oignionAct, SIGNAL(triggered()), this, SLOT(pelures()));
        vidAct = new QAction(this);
            vidAct = editMenu->addAction("Vidéo");
            vidAct->setCheckable(true);
            vidAct->setChecked(true);
            QObject::connect(vidAct, SIGNAL(triggered()), this, SLOT(video()));
        editMenu->addSeparator();
        QAction *playAct = new QAction(this);
            playAct = editMenu->addAction("Lecture/Pause");
            //playAct->setShortcut(QKeySequence(Qt::));
            QObject::connect(playAct, SIGNAL(triggered()), this, SLOT(playPause()));
        QAction *stopAct = new QAction(this);
            stopAct = editMenu->addAction("Stop");
            stopAct->setShortcut(QKeySequence(Qt::Key_Left));
            QObject::connect(stopAct, SIGNAL(triggered()), this, SLOT(stop()));
        QAction *nextAct = new QAction(this);
            nextAct = editMenu->addAction("Next");
            nextAct->setShortcut(QKeySequence(Qt::Key_Right));
            QObject::connect(nextAct, SIGNAL(triggered()), this, SLOT(next()));

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
            QObject::connect(stopButton, SIGNAL(triggered()), this, SLOT(stop()));
        this->playButton = new QAction(this);
            playButton = topBar->addAction(QIcon("../src/pictures/play.png"),"Play");
            QObject::connect(playButton, SIGNAL(triggered()), this, SLOT(playDraw()));
        this->pauseButton = new QAction(this);
            pauseButton = topBar->addAction(QIcon("../src/pictures/pause.png"),"Pause");
            pauseButton->setVisible(false);
            QObject::connect(pauseButton, SIGNAL(triggered()), this, SLOT(pauseDraw()));
        QAction *nextButton = new QAction(this);
            nextButton = topBar->addAction(QIcon("../src/pictures/next.png"),"Next");
            QObject::connect(nextButton, SIGNAL(triggered()), this, SLOT(next()));
        topBar->addSeparator();
        QAction *oignonButton = new QAction(this);
            QCheckBox *oignonCheck = new QCheckBox("Pelures d'Oignon");
            oignonButton = topBar->addWidget(oignonCheck);
            QObject::connect(oignonButton, SIGNAL(triggered()), this, SLOT(pelures()));
        QAction *nbOignon = new QAction(this);
            QSpinBox *oignonSpin = new QSpinBox;
                oignonSpin->setRange(1,5);
            nbOignon = topBar->addWidget(oignonSpin);
        vidButton = new QAction(this);
            QCheckBox *vidCheck = new QCheckBox("Vidéo");
            vidCheck->setChecked(true);
            vidButton = topBar->addWidget(vidCheck);
            QObject::connect(vidButton, SIGNAL(triggered()), this, SLOT(video()));

    //////////////////////////////
    /// Barre verticale gauche ///
    //////////////////////////////
    QToolBar *leftBar = new QToolBar(this);
        leftBar->setOrientation(Qt::Vertical);
        QAction *penButton = new QAction(this);
            penButton = leftBar->addAction(QIcon("../src/pictures/pen.png"),"Crayon");
            QObject::connect(penButton, SIGNAL(triggered()), this, SLOT(draw()));
        QAction *sizeButton = new QAction(this);
            QSpinBox *sizePen = new QSpinBox;
            sizePen->setRange(1,50);
            sizeButton = leftBar->addWidget(sizePen);
            QObject::connect(sizePen, SIGNAL(valueChanged(int)), this, SLOT(setPenSize(int)));
        QAction *eraserButton = new QAction(this);
            eraserButton = leftBar->addAction(QIcon("../src/pictures/eraser.png"),"Gomme");
            QObject::connect(eraserButton, SIGNAL(triggered()), this, SLOT(erase()));
        this->colorButton = new QAction(this);
            colorButton = leftBar->addAction("Couleur");
            QObject::connect(colorButton, SIGNAL(triggered()), this, SLOT(showPicker()));
        QAction *backButton = new QAction(this);
            backButton = leftBar->addAction(QIcon("../src/pictures/back.png"),"Annuler");
            QObject::connect(backButton, SIGNAL(triggered()), this, SLOT(undo()));

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

void Gui::draw()
{
    //TODO
}

void Gui::setPenSize(int i)
{
    drawingZone->setPenSize(i);
}

void Gui::erase()
{
    //TODO efface à la taille du crayon
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

void Gui::undo()
{
    //TODO annuler action
}

void Gui::redo()
{
    //TODO
}

void Gui::newProject()
{
    //TODO
}

void Gui::openProject()
{
    //TODO
}

void Gui::save()
{
    //TODO
}

void Gui::saveAs()
{
    //TODO
}

void Gui::imgExport()
{
    //TODO
}

void Gui::vidExport()
{
    //TODO
}

void Gui::closeProject()
{
    //TODO
}

void Gui::stop()
{
    //TODO stop lecture + retour début dessin
    playButton->setVisible(true);
    pauseButton->setVisible(false);
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

void Gui::playPause()
{
    if(playButton->isVisible())
        playDraw();
    else
        pauseDraw();
}

void Gui::next()
{
    //TODO
}

void Gui::pelures()
{
    //TODO
}

void Gui::video()
{
    //TODO afficher/enlever vidéo
    //"relier" vidAct et vidButton
}

Gui::~Gui()
{
    delete ui;
}

