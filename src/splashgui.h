#ifndef SPLASHGUI_H
#define SPLASHGUI_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

class SplashGui : public QWidget
{
    QGridLayout* layout;
    QLabel* title;
    QLabel* description;
    QPushButton* newProject;
    QPushButton* openProject;
    QPushButton* quit;
    Q_OBJECT
public:
    explicit SplashGui();

signals:

public slots:

};

#endif // SPLASHGUI_H
