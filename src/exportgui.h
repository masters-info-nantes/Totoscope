#ifndef EXPORTGUI_H
#define EXPORTGUI_H

#include <QWidget>
#include <QTabWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

class ExportGui : public QWidget
{
    Q_OBJECT
    QLineEdit* dirEdit;
    QPushButton* browse;
    QComboBox* codecBox;
    QLineEdit* vidEdit;
    QComboBox* formatBox;


public:
    explicit ExportGui(int i,QWidget *parent = 0);
    ~ExportGui();

signals:

public slots:

};

#endif // EXPORTGUI_H
