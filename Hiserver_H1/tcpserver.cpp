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
        QByteArray buf = readAll();
        QString stringbuf = buf;
        for(int i = 0; i < stringbuf.size(); i++)
        {
            if(stringbuf[i]==char(2))
            {
                msg = "";
                continue;
            }else if(stringbuf[i]==char(3))
            {
                emit updataClients(msg.toUtf8(),msg.toUtf8().size(),this->socketDescriptor());
                msg = "";
                continue;
            }
            msg += stringbuf[i];
        }
    }

    /*while(bytesAvailable()>0)
    {
        char buf[1];
        read(buf,1);
        if(buf[0]==char(2))
        {
            msg = "";
            continue;
        }else if(buf[0]==char(3))
        {
            emit updataClients(msg,msg.size(),this->socketDescriptor());
            msg = "";
            continue;
        }
        msg += buf[0];
    }*/
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
