#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "parasolid_kernel.h"
#include "glwidget.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
	GLWidget *w ;
private slots:
    void on_actionOpen_triggered();
	void ModelEdge();
	void ModelSolid();
};

#endif // MAINWINDOW_H
