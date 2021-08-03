#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include "tcpserver.h"

class server : public QTcpServer
{
    Q_OBJECT
public:
    server(QObject *parent,int port);
    QList<TcpServer*> tcpclientSocketlist;
signals:
    void updataServer(QString,int,int);
public slots:
    void updataClients(QString,int,int);
    void slotDisconnected(int);
protected:
    void incomingConnection(int socketDescriptor);
};

#endif // SERVER_H
