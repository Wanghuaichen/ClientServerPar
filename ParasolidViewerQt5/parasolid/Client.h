#ifndef Client_H
#define Client_H
#include <QTcpSocket>
#include <QHostAddress>
#include "D:/ClientServerPar/ParasolidServer/PsClient.h"



class Client : public QObject
{
  Q_OBJECT  

public:
    explicit Client();
	void PassFileToServer(QString );
    //~Client();
	struct PK_VECTOR_s {
		double coord[3];
	};
	typedef struct PK_VECTOR_s PK_VECTOR_t;

	QList<PK_VECTOR_t> *vertexList;
private slots:
    void onSokConnected();
    
    void onSokReadyRead();
   

private:
    QTcpSocket *_sok;
    quint16 _blockSize;
    QString _name;
    

};

#endif