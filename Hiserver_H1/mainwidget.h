#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QTimerEvent>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVector>
#include <QCryptographicHash>
#include <QProcess>
#include <QTimer>
#include "server.h"
#include "sql.h"


class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void send(QByteArray,int);
    void sendface(QString,int);
    void timerEvent(QTimerEvent *event);
    QString getrandkey();
    void sendlogin_files(QString account,int descriptor);
    void creatbatfiles(QString account);

private:
    QListWidget *ContentListWidget;
    QLabel *PortLabel;
    QLineEdit *PortLineEdit;
    QPushButton *CreateBtn;
    QGridLayout *mainLayout;
    int port;
    server *server;
    SQL *mysql;
    QString Filepath;
    QFile file;
    QMap<QString,int> user;
    QMap<int,QString>users;
    bool flashsql;
    QTimer delay;

    qint64 filesize;
    qint64 sendsize;
    QString filename;

public slots:
    void slotCreateServer();
    void connecttomysql(int);
    void updataServer(QString,int,int);
};
#endif // MAINWIDGET_H
