#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <socket.h>
#include <QFile>
#include <QObject>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent,int port);
    void sendfiles(QString ,int);

    QList<Socket*> tcpclientSocketlist;


signals:
    void get_msg(QByteArray,int);
    void sendok(QString msg);
public slots:
    void dataReceived(QByteArray,int);
    void clientDisconnected(int);
    void getok(QString msg);
protected:
    void incomingConnection(int socketDescriptor);
};

#endif // SERVER_H
