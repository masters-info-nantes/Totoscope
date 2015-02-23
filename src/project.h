#ifndef PROJECT_H
#define PROJECT_H

#include <QList>
#include <QImage>
#include <QString>
#include <QXmlStreamWriter>
#include <QFile>
class Project
{
    QString name;
    QString path;
    QList<QImage*>* drawings;
public:
    Project(QString aName, QString aVideofile, int aFramerate);
    Project(QString aPath);
    void save(QString aPath);
    void save();
    ~Project();
};

#endif // PROJECT_H
