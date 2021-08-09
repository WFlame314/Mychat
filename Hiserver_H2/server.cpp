#include "server.h"

Server::Server(QObject *parent,int port):QTcpServer(parent)
{
    listen(QHostAddress::Any,port);
}

void Server::incomingConnection(int socketDescriptor)
{
    Socket *tcpClientSocket = new Socket(this);
    connect(tcpClientSocket,&Socket::H_dataReceived,this,&Server::dataReceived);
    connect(tcpClientSocket,&Socket::clientDisconnected,this,&Server::clientDisconnected);
    connect(tcpClientSocket,&Socket::sendok,this,&Server::getok);
    tcpClientSocket->setSocketDescriptor(socketDescriptor);
    tcpclientSocketlist.append(tcpClientSocket);
}

void Server::dataReceived(QByteArray data,int descriptor)
{
    emit get_msg(data,descriptor);
}

void Server::clientDisconnected(int descriptor)
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


void Server::sendfiles(QString filename, int descriptor)
{
    for(int i=0;i<tcpclientSocketlist.count();i++)
    {
        Socket *item = tcpclientSocketlist.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            emit sendok("find");
            item->sendfile(filename);
            return;
        }
    }
    return;

}

void Server::getok(QString msg)
{
    emit sendok(msg);
}
