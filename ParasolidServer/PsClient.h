#ifndef PsCLIENT_H
#define PsCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QThreadPool>
#include <QRegExp>
#include <QWidget>
#include "PsServer.h"
class PsServer;

class PsClient : public QObject
{
    friend class PsServer;
    Q_OBJECT

public:
    static const QString constNameUnknown;
    static const quint8 comAutchReq = 1;
    static const quint8 comUsersOnline = 2;
    static const quint8 comUserJoin = 3;
    static const quint8 comUserLeft = 4;
    static const quint8 comMessageToAll = 5;
    static const quint8 comMessageToUsers = 6;
    static const quint8 comPublicServerMessage = 7;
    static const quint8 comPrivateServerMessage = 8;
    static const quint8 comAutchSuccess = 9;
    static const quint8 comQueryToServer = 10;
    static const quint8 passFileToServer = 11;
    static const quint8 comErrNameInvalid = 201;
    static const quint8 comErrNameUsed = 202;

    explicit PsClient(int desc, PsServer *serv, QObject *parent = 0);
    ~PsClient();
    void setName(QString name) {_name = name;}
    QString getName() const {return _name;}
    bool getAutched() const {return _isAutched;}
    void doSendCommand(quint8 comm) const;
    void doSendUsersOnline() const;

signals:
    void addUserToGui(QString name);
    void removeUserFromGui(QString name);
    void removeUser(PsClient *client);
    void messageToGui(QString message, QString from, const QStringList &users);

private slots:
    void onConnect();
    void onDisconnect();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError) const;

private:
    QTcpSocket *_sok;
    PsServer *_serv;
    quint16 _blockSize;
    QString _name;
    bool _isAutched;

};

#endif // PsCLIENT_H
