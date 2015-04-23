#include <QApplication>
#include "PsServer.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Dialog w;
   // w.show();

    PsServer* _serv = new PsServer(NULL, NULL);

     if (_serv->doStartServer(QHostAddress::LocalHost, 1234))
     {
        qDebug() << "Server started!" ;
     } else  qDebug() << "Server not started!";

    return a.exec();
}
