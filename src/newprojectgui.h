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
    QGridLayout* layout;
    QLineEdit* nameEdit;
    QPushButton* videoButton;
    QComboBox* selectFramerate;
    QLineEdit* videoEdit;
    QPushButton* createButton;
public:
    explicit NewProjectGui(QWidget *parent = 0);
    ~NewProjectGui();

signals:

public slots:
    void chooseVideo();
    void createProject();
};

#endif // NEWPROJECTGUI_H
