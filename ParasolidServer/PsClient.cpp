#include "PsClient.h"
#include <QMessageBox>

const QString PsClient::constNameUnknown = QString(".Unknown");

PsClient::PsClient(int desc, PsServer *serv, QObject *parent) :QObject(parent)
{

    _serv = serv;

    _isAutched = false;
    _name = constNameUnknown;

    _blockSize = 0;

    _sok = new QTcpSocket();

    _sok->setSocketDescriptor(desc);

    connect(_sok, SIGNAL(connected()), this, SLOT(onConnect()));
    connect(_sok, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
    connect(_sok, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(_sok, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));

    qDebug() << "Client connected" << desc;
}

PsClient::~PsClient()
{

}

void PsClient::onConnect()
{
    //never calls, socket already connected to the tcpserver
    //we just binding to this socket here: _sok->setSocketDescriptor(desc);
}

void PsClient::onDisconnect()
{
    qDebug() << "Client disconnected";

    if (_isAutched)
    {

        emit removeUserFromGui(_name);

        _serv->doSendToAllUserLeft(_name);

        emit removeUser(this);
    }
    deleteLater();
}

void PsClient::onError(QAbstractSocket::SocketError socketError) const
{

    QWidget w;
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(&w, "Error", "The host was not found");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(&w, "Error", "The connection was refused by the peer.");
        break;
    default:
        QMessageBox::information(&w, "Error", "The following error occurred: "+_sok->errorString());
    }
    
}

void PsClient::onReadyRead()
{
   qDebug() << "ready read " ;
    QDataStream in(_sok);

    if (_blockSize == 0) {
      
        if (_sok->bytesAvailable() < (int)sizeof(quint16))
            return;
       
        in >> _blockSize;
        qDebug() << "_blockSize now " << _blockSize;
    }
   
    if (_sok->bytesAvailable() < _blockSize)
        return;
    else
       
        _blockSize = 0;
    
    quint8 command;
    in >> command;
    qDebug() << "Received command " << command;
   


    switch(command)
    {
       
        case comAutchReq:
        {
           
            QString name;
            in >> name;
            
            if (!_serv->isNameValid(name))
            {
               
                doSendCommand(comErrNameInvalid);
                return;
            }
            
            if (_serv->isNameUsed(name))
            {
                
                doSendCommand(comErrNameUsed);
                return;
            }
           
            _name = name;
            _isAutched = true;
          
            doSendUsersOnline();
            
            emit addUserToGui(name);
          
            _serv->doSendToAllUserJoin(_name);
        }
        break;
        
        case comQueryToServer:
        {
            QString message;
            in >> message;
           
            _serv->doQueryToServer(message, _name);
           
            //emit messageToGui(message, _name, QStringList());
        }
        break;
        case passFileToServer:
        {
            QString data;
            in >> data;
         
            _serv->loadFile(data);
           
            //emit messageToGui(message, _name, QStringList());
        }
        break;
     
        case comMessageToUsers:
        {
            QString users_in;
            in >> users_in;
            QString message;
            in >> message;
          
            QStringList users = users_in.split(",");
           
            _serv->doSendMessageToUsers(message, users, _name);
         
            emit messageToGui(message, _name, users);
        }
        break;
    }

    //for (long long i = 0; i < 4000000000; ++i){}
}

void PsClient::doSendCommand(quint8 comm) const
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << comm;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
    qDebug() << "Send to" << _name << "command:" << comm;
}

void PsClient::doSendUsersOnline() const
{
    
}





