#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpSocket>
#include <QObject>

class TcpServer : public QTcpSocket
{
    Q_OBJECT
private:
    QString msg;
    char filebuf[1024];
    int p;
    bool filemodel;
public:
    TcpServer(QObject *parent=0);
    void setfilemode(bool model);
signals:
    void datareceived(QString,int);
    void filereceived(char* buf);
    void disconnected(int);
protected slots:
    void dataReceived();
    void slotDisconnected();
};

#endif // TCPSERVER_H
