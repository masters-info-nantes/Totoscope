#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>
#include <project.h>
#include <QObject>
#include <QPixmap>
#include <QImage>
class Controller : public QObject
{
    Q_OBJECT

    Project* project;
    int currentImageIndex;
public:
    Controller();
    bool isProjectSaved();
signals:
    void projectCreated();
public slots:
    void openProject(QString path);
    void handleProjectCreation();
    void createProject(QString aName, QString aVideofile, int aFramerate);
    void saveProject();
    void saveProject(QString);
    void exportVideo(QString);
    void exportImages(QString);
    QPixmap* getPicture();

    QList<QPixmap*>* getPictures();
    QList<QImage*>* getOnions(int);
    QImage* getDrawing();
    void firstFrame();
    void nextFrame();
    void previousFrame();
    void setFrame(int);
};

#endif // CONTROLLER_H
