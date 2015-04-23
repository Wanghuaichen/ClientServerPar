#include "mainwindow.h"
#include "Session.h"
#include "parasolid_kernel.h"
#include <qpushbutton.h>
#include <qtoolbutton.h>
#include <qtablewidget.h>
#include <qtextdocument.h>
#include <qtextdocumentwriter.h>
#include <qtextedit.h>
#include "ParasolidDoc.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
	QTabWidget *tb = new QTabWidget();
	QToolButton *bt = new QToolButton();
	QToolButton *bt2 = new QToolButton();
	
	mainToolBar->addWidget(bt);
	mainToolBar->addSeparator();
	mainToolBar->addWidget(bt2);
	mainToolBar->addSeparator();
	connect(bt, SIGNAL(clicked()), SLOT(ModelSolid()));
	connect(bt2, SIGNAL(clicked()), SLOT(ModelEdge()));
	w = new GLWidget;
	
	setCentralWidget(w);
	
}

void MainWindow::on_actionOpen_triggered()
{
	  
	   w->check = 1;
	   w->OnOpenFile();
	   //QTextEdit *ed = new QTextEdit(primitive);
	   
	  

}
void MainWindow::ModelSolid()
{
	w->check = 1;
	w->updateGL();
}
void MainWindow::ModelEdge()
{
	w->check = 2;
	w->updateGL();
}




