#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<videodecomposer.h>
#include <QString>
#include <project.h>
#include <QObject>
class Controller : public QObject
{
    Q_OBJECT

    VideoDecomposer* decomposer;
    Project* project;
public:
    Controller();

public slots:
    void openProject(QString path);
    void createProject(QString aName, QString aVideofile, int aFramerate);
    void saveProject();
    void saveProject(QString pat);
};

#endif // CONTROLLER_H
