#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>

class myserver: public QTcpServer {
    Q_OBJECT
public:
    myserver();
    ~myserver();
public slots:
    void startServer();
    void incomingConnection(int socketDescriptor);
    void sockReady();
    void sockDisc();
private:
    QTcpSocket* socket;
    QByteArray Data;
    QSet<QTcpSocket*> clients_;
    QMap<QTcpSocket*, QString> users_;
};
#endif // MYSERVER_H
