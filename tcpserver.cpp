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
            emit datareceived(msg,msg.size());
            msg = "";
            continue;
        }
        msg += buf[0];
    }
}

void TcpServer::slotDisconnected()
{
    emit disconnected(this->socketDescriptor());
}
