#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpSocket>
#include <QObject>

class TcpServer : public QTcpSocket
{
    Q_OBJECT
private:
    QString msg;
public:
    TcpServer(QObject *parent=0);
signals:
    void updataClients(QString,int,int);
    void disconnected(int);
protected slots:
    void dataReceived();
    void slotDisconnected();
};

#endif // TCPSERVER_H
