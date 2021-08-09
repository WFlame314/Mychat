#ifndef SOCKET_H
#define SOCKET_H

#include <QTcpSocket>
#include <QDataStream>
#include <QObject>
#include <QFile>
#include <QDir>

class Socket : public QTcpSocket
{
    Q_OBJECT
public:
    Socket(QObject *);
    qint64 send(QByteArray data);
    void sendfile(QString filename);
    void setfile_size(int size);
private:
    QByteArray msg_data;
    QByteArray file_data;
    QFile filebuf;
    QByteArray msg_buf;
    bool filemode_send;
    bool filemode_recevie;

    qint64 m_totalBytes;
    qint64 m_bytesWritten;
    qint64 m_bytesToWrite;
    qint64 m_payloadSize;
    QByteArray m_outBlock;

    int filesize;
    int receviedsize;

protected:
    void filetemp(QByteArray data);
signals:
    void H_dataReceived(QByteArray data,int descriptor);
    void H_fileReceived(QByteArray data,int descriptor);
    void clientDisconnected(int);
    void H_Byteswriten(qint64,int);

public slots:
    void dataReceived();
    void slotDisconnected();
    void getBytesW(qint64);
};

#endif // SOCKET_H
