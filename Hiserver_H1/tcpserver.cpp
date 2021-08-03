#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
}

void TcpServer::dataReceived()
{
    while(bytesAvailable()>0)
    {
        char buf[1];
        read(buf,1);
        if(buf[0]==char(0))
        {
            msg = "";
            continue;
        }else if(buf[0]==char(1))
        {
            emit updataClients(msg,msg.size(),this->socketDescriptor());
            msg = "";
            continue;
        }
        msg += buf[0];
    }
    /*while(bytesAvailable()>0)
    {
        int length = bytesAvailable();
        char buf[length];
        read(buf,length);
        QString msg=buf;
        emit updataClients(msg,length,this->socketDescriptor());
    }*/
}

void TcpServer::slotDisconnected()
{
    emit disconnected(this->socketDescriptor());
}
