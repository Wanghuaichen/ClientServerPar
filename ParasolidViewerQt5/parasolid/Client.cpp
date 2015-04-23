#include <Client.h>

Client :: Client()
{
	_sok = new QTcpSocket();

	 _sok->connectToHost(QHostAddress::LocalHost, 1234);
	connect(_sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    connect(_sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
	vertexList = new QList<PK_VECTOR_t>();

}

void Client::onSokReadyRead()
{
    qDebug() << "ready ";
	QDataStream in(_sok);
   //тут обрабатываются данные от сервера
    if (_blockSize == 0) {
        //если считываем новый блок первые 2 байта это его размер
        if (_sok->bytesAvailable() < (int)sizeof(quint16))
            return;
        //считываем размер (2 байта)
        in >> _blockSize;
        qDebug() << "_blockSize now " << _blockSize;
    }
 //ждем пока блок прийдет полностью
    if (_sok->bytesAvailable() < _blockSize)
        return;
    else
       //можно принимать новый блок
        _blockSize = 0;
    //3 байт - команда серверу
    quint8 command;
    in >> command;
    qDebug() << "Received command " << command;

    switch (command)
    {
       
        case PsClient::comQueryToServer:
        {
            QString user;
            in >> user;
            QString message, msg;
            double arr;
            in >> message;
			msg = message.split("|").at(1);
			arr = msg.split(",").at(0).toDouble();
           
            QString str("22");
            int a = str.toInt();
			qDebug() << arr;
            //AddToLog("["+user+"]: "+a);
        }
        break;
		 case PsClient::passFileToServer:
        {
            QStringList list; PK_VECTOR_t vect;
            QString message, msg;
            double arr;
            in >> message;
			qDebug() << message;
			list = message.split(",");
			int size = (int)(list.size() - 1)/3;
			int t = 1; //vertexList->clear();
			for(int i = 1; i <= size; i++)
			{
				for(int n = 0; n < 3; n++)
				{
					vect.coord[n] = list.at(t).toDouble(); t++;
					
				}
				vertexList->push_back(vect);
				
			}

			qDebug() << vertexList->size();
        }
        break;
       
    }
}

void Client::onSokConnected()
{
    _blockSize = 0;
	   qDebug() << "connect ";
    //try autch
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << (quint8)PsClient::comQueryToServer;
	QString go = "go11111";
    out <<go;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
}

void Client :: PassFileToServer(QString data)
{
	_blockSize = 0;
	   qDebug() << "PassFileToServer ";
	    qDebug() << data;
    //try autch
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << (quint8)PsClient::passFileToServer;
    out <<data;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
}


