#ifndef PsSERVER_H
#define PsSERVER_H

#include <QTcpServer>
#include "PsClient.h"
#include "parasolid_kernel.h"
#include <QFile>
#include "Session.h"
class PsClient;

class PsServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit PsServer(QWidget *widget = 0, QObject *parent = 0);
    bool doStartServer(QHostAddress addr, qint16 port);
    void doSendToAllUserJoin(QString name);
    void doSendToAllUserLeft(QString name);
    void doSendToAllMessage(QString message, QString fromUsername);
    void doQueryToServer(QString message, QString fromUsername);
    void loadFile(QString data);
    void doSendToAllServerMessage(QString message);
    void doSendServerMessageToUsers(QString message, const QStringList &users);
    void doSendMessageToUsers(QString message, const QStringList &users, QString fromUsername);
    bool isNameValid(QString name) const;
    bool isNameUsed(QString name) const;
	void sendFileToClient(QString data);

signals:
    void addLogToGui(QString string, QColor color);

public slots:
    void onMessageFromGui(QString message, const QStringList &users);
    void onRemoveUser(PsClient *client);

protected:
    void incomingConnection(int handle);

private:
    QList<PsClient *> _clients;
    QWidget *_widget;
public:
    PK_SESSION_frustrum_t m_frustrum;
    PK_SESSION_frustrum_t m_oldfrustrum;
    int m_nparts;
    PK_PART_t* m_parts;
    int m_ngeoms;
    PK_GEOM_t* m_geoms;

};

#endif // PsSERVER_H
