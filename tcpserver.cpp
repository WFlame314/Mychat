#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent)
{
    filemodel = false;
    p=0;
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));

}

void TcpServer::dataReceived()
{
    /*QByteArray buf = readAll();
    QString stringbuf = buf;
    if(filemodel == false)
    {
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
    }else
    {
        emit filereceived(buf.data());
    }*/
    qDebug()<<bytesAvailable();
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
        qint64 len;
        while(bytesAvailable()>0)
        {
            len = bytesAvailable();
            if(len+p <= 1024)
            {
                read(filebuf+p,len);
                p += len;
                continue;
            }else
            {
                read(filebuf+p,1024-p);
                p=0;
                emit filereceived(filebuf);
            }
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
