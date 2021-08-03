#include "server.h"

server::server(QObject *parent,int port):QTcpServer(parent)
{
    listen(QHostAddress::Any,port);
}

void server::incomingConnection(int socketDescriptor)
{
    TcpServer *tcpClientSocket = new TcpServer(this);
    connect(tcpClientSocket,SIGNAL(updataClients(QString,int,int)),this,SLOT(updataClients(QString,int,int)));
    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected(int)));
    tcpClientSocket->setSocketDescriptor(socketDescriptor);
    tcpclientSocketlist.append(tcpClientSocket);
}

void server::updataClients(QString msg,int length,int descriptor)
{
    emit updataServer(msg,length,descriptor);
    /*for(int i=0;i<tcpclientSocketlist.count();i++)
    {
        QTcpSocket *item = tcpclientSocketlist.at(i);
        if(item->write(msg.toLatin1(),length)!=length)
        {
            continue;
        }
    }*/
}

void server::slotDisconnected(int descriptor)
{
    for(int i=0;i<tcpclientSocketlist.count();i++)
    {
        QTcpSocket *item = tcpclientSocketlist.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            tcpclientSocketlist.removeAt(i);
            return;
        }
    }
    return;
}
