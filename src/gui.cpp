#include "gui.h"
#include "ui_gui.h"

Gui::Gui(Controller* aController) :
    QWidget(0),controller(aController), ui(new Ui::Gui)
{
    //this->setStyleSheet("background:#3A3A3A;color:white;");
    this->setMinimumSize(800,600);
    this->setWindowTitle("Totoscope");
    ui->setupUi(this);
    QGridLayout* layout = new QGridLayout();

    ////////////////////////////
    /// Barre Menu principal ///
    ////////////////////////////

    menuBar = new QMenuBar(this);
    //menuBar->setStyleSheet("background:#545454;");
    menuBar->setMinimumHeight(30);
    QMenu *fileMenu = new QMenu;
        fileMenu = menuBar->addMenu(tr("&Fichier"));
        //fileMenu->setStyleSheet("background:#545454;");
        QAction *newAct = new QAction(this);
            newAct = fileMenu->addAction("Nouveau Projet");
            newAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
            QShortcut *newCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_N),this);
            QObject::connect(newCut, SIGNAL(activated()), this, SLOT(newProject()));
            QObject::connect(newAct, SIGNAL(triggered()), this, SLOT(newProject()));
        QAction *openAct = new QAction(this);
            openAct = fileMenu->addAction("Ouvrir Projet");
            openAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
            QShortcut *openCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O),this);
            QObject::connect(openCut, SIGNAL(activated()), this, SLOT(openProject()));
            QObject::connect(openAct, SIGNAL(triggered()), this, SLOT(openProject()));
        fileMenu->addSeparator();
        QAction *saveAct = new QAction(this);
            saveAct = fileMenu->addAction("Enregistrer");
            saveAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
            QShortcut *saveCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S),this);
            QObject::connect(saveCut, SIGNAL(activated()), this, SLOT(save()));
            QObject::connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));
        QAction *saveAsAct = new QAction(this);
            saveAsAct = fileMenu->addAction("Enregistrer sous");
            saveAsAct->setShortcut(QKeySequence(Qt::CTRL +Qt::SHIFT + Qt::Key_S));
            QShortcut *saveAsCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S),this);
            QObject::connect(saveAsCut, SIGNAL(activated()), this, SLOT(saveAs()));
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
            closeAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));
            QShortcut *closeCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W),this);
            QObject::connect(closeCut, SIGNAL(activated()), this, SLOT(closeProject()));
            QObject::connect(closeAct, SIGNAL(triggered()), this, SLOT(closeProject()));
        QAction *exitAct = new QAction(this);
            exitAct = fileMenu->addAction("Quitter");
            exitAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
            QShortcut *exitCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q),this);
            QObject::connect(exitCut, SIGNAL(activated()), QApplication::instance(), SLOT(quit()));
            QObject::connect(exitAct, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));

    QMenu *editMenu = new QMenu;
        editMenu = menuBar->addMenu(tr("&Edition"));
        QAction *undoAct = new QAction(this);
            undoAct = editMenu->addAction("Annuler");
            undoAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
            QShortcut *undoCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z),this);
            QObject::connect(undoCut, SIGNAL(activated()), this, SLOT(undo()));
            QObject::connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));
        QAction *redoAct = new QAction(this);
            redoAct = editMenu->addAction("Retablir");
            redoAct->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Z));
            QShortcut *redoCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Z),this);
            QObject::connect(redoCut, SIGNAL(activated()), this, SLOT(redo()));
            QObject::connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));
        editMenu->addSeparator();
        oignionAct = new QAction(this);
            oignionAct = editMenu->addAction("Pelures d'Oignon");
            oignionAct->setCheckable(true);
            QObject::connect(oignionAct, SIGNAL(triggered()), this, SLOT(updateDrawingZone()));
        vidAct = new QAction(this);
            vidAct = editMenu->addAction("Vidéo");
            vidAct->setCheckable(true);
            vidAct->setChecked(true);
            QObject::connect(vidAct, SIGNAL(triggered()), this, SLOT(video()));
        editMenu->addSeparator();
        QAction *playAct = new QAction(this);
            playAct = editMenu->addAction("Lecture/Pause");
            playAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
            QShortcut *playCut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_P),this);
            QObject::connect(playCut, SIGNAL(activated()), this, SLOT(playPause()));
            QObject::connect(playAct, SIGNAL(triggered()), this, SLOT(playPause()));
        QAction *stopAct = new QAction(this);
            stopAct = editMenu->addAction("Stop");
            stopAct->setShortcut(QKeySequence(Qt::Key_Left));
            QShortcut *stopCut = new QShortcut(QKeySequence(Qt::Key_Left),this);
            QObject::connect(stopCut, SIGNAL(activated()), this, SLOT(stop()));
            QObject::connect(stopAct, SIGNAL(triggered()), this, SLOT(stop()));
        QAction *nextAct = new QAction(this);
            nextAct = editMenu->addAction("Next");
            nextAct->setShortcut(QKeySequence(Qt::Key_Right));
            QShortcut *nextCut = new QShortcut(QKeySequence(Qt::Key_Right),this);
            QObject::connect(nextCut, SIGNAL(activated()), this, SLOT(next()));
            QObject::connect(nextAct, SIGNAL(triggered()), this, SLOT(next()));

    QMenu *helpMenu = new QMenu;
        helpMenu = menuBar->addMenu(tr("&Aide"));
        QAction *aboutAct = new QAction(this);
            aboutAct = helpMenu->addAction("A Propos");
            QObject::connect(aboutAct, SIGNAL(triggered()), this, SLOT(showMessage()));

    //////////////////////////////
    /// Barre horizontale haut ///
    //////////////////////////////

    topBar = new QToolBar(this);
        //topBar->setStyleSheet("QToolBar {background:lightgrey;}");
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
            QObject::connect(oignonButton, SIGNAL(triggered()), this, SLOT(updateDrawingZone()));
        QAction *nbOignon = new QAction(this);
            oignonSpin = new QSpinBox;
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

    leftBar = new QToolBar(this);
        leftBar->setOrientation(Qt::Vertical);
        //leftBar->setStyleSheet("QToolBar {background:lightgrey;}");
        QAction *penButton = new QAction(this);
            penButton = leftBar->addAction(QIcon("../src/pictures/pen.png"),"Crayon");

        QAction *sizeButton = new QAction(this);
            QSpinBox *sizePen = new QSpinBox;
            sizePen->setRange(1,50);
            sizePen->setValue(3);
            sizeButton = leftBar->addWidget(sizePen);
            QObject::connect(sizePen, SIGNAL(valueChanged(int)), this, SLOT(setPenSize(int)));
        QAction *eraserButton = new QAction(this);

            eraserButton = leftBar->addAction(QIcon("../src/pictures/eraser.png"),"Gomme");

        this->colorButton = new QAction(this);
            colButton = new QPushButton;
            colButton->setStyleSheet("background-color:black;");
            colorButton = leftBar->addWidget(colButton);
            QObject::connect(colButton, SIGNAL(clicked()), this, SLOT(showPicker()));
        QAction *backButton = new QAction(this);
            backButton = leftBar->addAction(QIcon("../src/pictures/back.png"),"Annuler");


    ///////////////////////////////
    /// Barre de défilement bas ///
    ///////////////////////////////

    scrollBar = new QScrollArea;
        QWidget *scrollWidget = new QWidget;
        scrollBar->setFixedHeight(120);
            QHBoxLayout *hblayout = new QHBoxLayout;
            int ind= 0;
            QList<QPixmap*>* thumbnails = this->controller->getPictures();
            for(int i=0;i<thumbnails->length();i++)
            {
                Thumbnail *thumb = new Thumbnail(thumbnails->at(i),i);

                QObject::connect(thumb,SIGNAL(clicked(int)),this,SLOT(showThumb(int)));
                hblayout->addWidget(thumb);
            }
        scrollWidget->setLayout(hblayout);
    scrollBar->setWidget(scrollWidget);

    /////////////////////////
    /// Drawing management //
    /////////////////////////

    this->drawingZone = new DrawingZone();
    this->setLayout(layout);
    //this->layout()->setMargin(0);
    layout->addWidget(menuBar,0,0,1,6);
    layout->addWidget(topBar,1,3);
    layout->addWidget(leftBar,2,0);
    layout->addWidget(drawingZone,2,1,1,5);
    layout->addWidget(scrollBar,3,1,1,4);
    QPushButton* nextImage = new QPushButton(">");
    QPushButton* previousImage = new QPushButton("<");
    previousImage->setMaximumWidth(50);
    previousImage->setMinimumHeight(100);
    nextImage->setMaximumWidth(50);
    nextImage->setMinimumHeight(100);
    QObject::connect(previousImage,SIGNAL(clicked()),this,SLOT(previousFrame()));
    QObject::connect(nextImage,SIGNAL(clicked()),this,SLOT(nextFrame()));
    layout->addWidget(previousImage,3,0);
    layout->addWidget(nextImage,3,5);

    drawingZone->setVideoFrame(this->controller->getPicture());
    drawingZone->setImage(this->controller->getDrawing());

    timer = new QTimer();
    timer->setInterval(500);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    QObject::connect(penButton,SIGNAL(triggered()),this->drawingZone,SLOT(choosePen()));
    QObject::connect(eraserButton,SIGNAL(triggered()),this->drawingZone,SLOT(chooseRubber()));
               QObject::connect(backButton, SIGNAL(triggered()), this->drawingZone, SLOT(undoImage()));
}


void Gui::setPenSize(int i)
{
    drawingZone->setPenSize(i);
}


void Gui::showPicker()
{
    this->colorPalette = new QColorDialog();
    colorPalette->setModal(true);
    QObject::connect(colorPalette, SIGNAL(colorSelected(QColor)), this, SLOT(changeColor(QColor)));
    colorPalette->open();
}

void Gui::changeColor(QColor newcolor)
{
    colButton->setStyleSheet("background-color:"+newcolor.name()+";");
    drawingZone->setPenColor(newcolor);
}

void Gui::undo()
{
    //TODO annuler action
}

void Gui::showThumb(int index)
{
    this->controller->setFrame(index);
    updateDrawingZone();
}

void Gui::nextFrame()
{
    this->controller->nextFrame();
    updateDrawingZone();
}

void Gui::previousFrame()
{
    this->controller->previousFrame();
    updateDrawingZone();
}

void Gui::updateDrawingZone()
{
    drawingZone->setVideoFrame(this->controller->getPicture());
    drawingZone->setImage(this->controller->getDrawing());
    if(this->oignionAct->isChecked())
        drawingZone->showOnions(this->controller->getOnions(this->oignonSpin->value()));
    else
        drawingZone->hideOnions();
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
    if(this->controller->isProjectSaved())
        this->controller->saveProject();
    else
        saveAs();
}

void Gui::saveAs()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    this->controller->saveProject(dir+"/");
}

void Gui::imgExport()
{
    //TODO
    ExportGui *exportWin = new ExportGui(0,this->controller);
    exportWin->show();
}

void Gui::vidExport()
{
    //TODO
    ExportGui *exportWin = new ExportGui(1,this->controller);
    exportWin->show();
}

void Gui::closeProject()
{
    this->close();
}

void Gui::stop()
{
    //TODO retour début dessin
    playButton->setVisible(true);
    pauseButton->setVisible(false);
    timer->stop();
}

void Gui::playDraw()
{
    playButton->setVisible(false);
    pauseButton->setVisible(true);
    timer->start();
}

void Gui::pauseDraw()
{
    playButton->setVisible(true);
    pauseButton->setVisible(false);
    timer->stop();

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


void Gui::video()
{
    if(vidAct->isChecked())
        this->drawingZone->showVideo();
    else
        this->drawingZone->hideVideo();
}

void Gui::resizeEvent()
{
   // this->frameWidget->resize();
    //this->frameWidget->setPixmap(this->frameWidget->pixmap()->scaled(this->frameWidget->width(),this->frameWidget->height()));
}

void Gui::showMessage()
{
    QMessageBox *aboutBox = new QMessageBox;
        aboutBox->setWindowTitle(tr("A Propos"));
        aboutBox->setText("Logiciel dévelopé par Marie Lenogue et Nicolas Brondin");
        aboutBox->setInformativeText("Université de Nantes - 2015");
        aboutBox->setStandardButtons(QMessageBox::Ok);
        aboutBox->setDefaultButton(QMessageBox::Ok);
        aboutBox->exec();
}

Gui::~Gui()
{
    delete ui;
    delete menuBar;
    delete topBar;
    delete leftBar;
    delete scrollBar;
}

