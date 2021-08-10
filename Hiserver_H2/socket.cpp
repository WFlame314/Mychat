#include "socket.h"

Socket::Socket(QObject *)
{
    m_payloadSize = 64 * 1024;
    m_totalBytes = 0;
    m_bytesWritten = 0;
    m_bytesToWrite = 0;
    msg_buf = "";
    filemode_send=false;
    filemode_recevie = false;
    connect(this,&QTcpSocket::readyRead,this,&Socket::dataReceived);
    connect(this,&QTcpSocket::disconnected,this,&Socket::slotDisconnected);
    connect(this,&QTcpSocket::bytesWritten,this,&Socket::getBytesW);
}

void Socket::dataReceived()
{
    while(bytesAvailable()>0)
    {
        QByteArray buf = readAll();
        for(int i = 0; i < buf.size(); i++)
        {
            if(filemode_recevie == false)
            {
                if(buf[i]==char(2))
                {
                    msg_data = "";
                    continue;
                }else if(buf[i]==char(3))
                {
                    emit H_dataReceived(msg_data,this->socketDescriptor());
                    msg_data = "";
                    continue;
                }else if(buf[i]==char(1))
                {
                    receviedsize = 0;
                    filemode_recevie = true;
                    continue;
                }
                msg_data += buf[i];
            }else
            {
                receviedsize ++;
                file_data += buf[i];
                if(receviedsize == filesize)
                {
                    emit H_fileReceived(file_data,this->socketDescriptor());
                    filesize=0;
                    receviedsize = 0;
                    filemode_recevie = false;
                }
            }
        }
    }
}


void Socket::slotDisconnected()
{
    emit clientDisconnected(this->socketDescriptor());
}

void Socket::getBytesW(qint64 num)
{
    if(filemode_send == false)
    {
        msg_buf = "";
    }else
    {
        m_bytesWritten += (int)num;
        qDebug()<<m_bytesWritten<<" "<<num<<" "<<m_totalBytes;
        if(m_bytesToWrite>0){
            m_outBlock=filebuf.read(qMin(m_bytesToWrite,m_payloadSize));
            m_bytesToWrite-=(int)this->write(m_outBlock);
            m_outBlock.resize(0);
        }
        else{
            filebuf.close();
        }
        if(m_bytesWritten==m_totalBytes){
            filebuf.close();
            filemode_send = false;
            emit sendok("发送完成");
        }
    }

}

qint64 Socket::send(QByteArray data)
{
    msg_buf += data;
    if(filemode_send == false)
    {
        qint64 len;
        len = this->write(msg_buf);
        return len;
    }
    return 0;
}

void Socket::sendfile(QString filename)
{
    filebuf.setFileName(filename);
    if(filebuf.open(QIODevice::ReadOnly))
    {
        emit sendok("打开成功");
        filemode_send=true;
        m_totalBytes=filebuf.size();
        m_bytesToWrite = filebuf.size();
        m_totalBytes += this->write(QString(char(1)).toUtf8());
    }
}

void Socket::setfile_size(int size)
{
    filesize = size;
}
