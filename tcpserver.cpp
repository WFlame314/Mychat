#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent)
{
    filemodel = false;
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));

}

void TcpServer::dataReceived()
{
    if(filemodel == false)
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
                    emit datareceived(msg.toUtf8(),msg.toUtf8().size());
                    msg = "";
                    continue;
                }
                msg += stringbuf[i];
            }
        }
    }else
    {
        while(bytesAvailable()>0)
        {
             QByteArray buf = readAll();
             emit filereceived(buf);
        }
    }

}

void TcpServer::slotDisconnected()
{
    emit disconnected(this->socketDescriptor());
}

void TcpServer::setfilemode(bool model)
{
    filemodel = model;
}
