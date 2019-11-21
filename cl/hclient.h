#ifndef HCLIENT_H
#define HCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

class mClient :public QObject{
    Q_OBJECT
public:
    explicit mClient(QObject* parent = nullptr);
    ~mClient();
    void sockStart(QString& name);
public slots:
    void sockReady();
    void sockESC();
    void message_entered(QString message);

private:
   QString Name;
   QTcpSocket* socket;
   QByteArray Data;
};
#endif // HCLIENT_H
