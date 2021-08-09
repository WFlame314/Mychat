#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>
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


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void timerEvent(QTimerEvent *);
    int send(QByteArray backmsg,int descriptor);
    QString getrandkey();
    void creatbatfiles(QString account);
    void sendlogin_files(QString account,int descriptor);
    void sendlogin_files_head(QString account,int descriptor);

private:
    Ui::Widget *ui;
    QListWidget *ContentListWidget;
    QLabel *PortLabel;
    QLineEdit *PortLineEdit;
    QPushButton *CreateBtn;
    QGridLayout *mainLayout;

    int port;
    bool flashsql;
    int filesize;

    SQL *mysql;
    Server *H_server;

public slots:
    void slotCreateServer();
    void connecttomysql(int type);
    void dataReceived(QByteArray data,int);
    void getok(QString msg);
};
#endif // WIDGET_H
