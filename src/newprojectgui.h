#ifndef NEWPROJECTGUI_H
#define NEWPROJECTGUI_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QFileDialog>
#include <gui.h>

class NewProjectGui : public QWidget
{
    Q_OBJECT
    Controller* controller;
    QGridLayout* layout;
    QLabel* error;
    QLineEdit* nameEdit;
    QPushButton* videoButton;
    QComboBox* selectFramerate;
    QLineEdit* videoEdit;
    QPushButton* createButton;
public:
    explicit NewProjectGui(Controller* controller);
    ~NewProjectGui();

signals:

public slots:
    void chooseVideo();
    void createProject();
    void nextWindow();
};

#endif // NEWPROJECTGUI_H
