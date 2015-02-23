#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>
#include <project.h>
#include <QObject>
class Controller : public QObject
{
    Q_OBJECT

    Project* project;
public:
    Controller();

signals:
    void projectCreated();
public slots:
    void openProject(QString path);
    void handleProjectCreation();
    void createProject(QString aName, QString aVideofile, int aFramerate);
    void saveProject();
    void saveProject(QString pat);
};

#endif // CONTROLLER_H
