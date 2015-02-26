#ifndef EXPORTGUI_H
#define EXPORTGUI_H

#include <QWidget>
#include <QTabWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QFileDialog>
#include <controller.h>

class ExportGui : public QWidget
{
    Q_OBJECT
    QLineEdit* dirEdit;
    QPushButton* browse;
    QComboBox* codecBox;
    QLineEdit* vidEdit;
    QComboBox* formatBox;
    Controller* controller;


public:
    explicit ExportGui(int i,Controller*);
    ~ExportGui();

signals:

public slots:
        void exportVideo();

};

#endif // EXPORTGUI_H
