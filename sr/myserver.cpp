#include "hserver.h"

myserver::myserver(){}

myserver::~myserver(){}

void myserver::startServer() { //старт
    if (this->listen(QHostAddress::Any,3122))
    {
        qDebug()<<"Listening";
    }
    else
    {
        qDebug()<<"Not listening";
    }
}

void myserver::incomingConnection(int socketDescriptor) {
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    clients_.insert(socket);

    connect (socket, &QTcpSocket::readyRead,this,&myserver::sockReady);
    connect (socket, &QTcpSocket::disconnected,this,&myserver::sockDisc);

    qDebug()<<socketDescriptor<<" Client connected";
    socket->write("You are connected! Write you message");
    qDebug()<<"First msg for client number:"<<socketDescriptor<<" was sent";
}

void myserver::sockReady() { // чтение дата
    QTcpSocket* client = dynamic_cast<QTcpSocket*> (sender());
    while(client->canReadLine()){
        QString user;
        users_[client] = user;

        QString line = QString::fromUtf8(client->readLine()).trimmed(); // получение смс
        QString message=line;

        QTextStream(stdout) <<user<< " "<< message << "\n";

        foreach (QTcpSocket* other_client, clients_) { //отправка другим юзерам
            other_client->write(QString(message).toUtf8());
        }
    }
}

void myserver::sockDisc() { //на выход юзера
    QTcpSocket* client = dynamic_cast<QTcpSocket*> (sender());

    QTextStream(stdout) << "Client disconnected\n";

    clients_.remove(client);
    foreach (QTcpSocket* client, clients_) {
        client->write(QString("Server: another has left.\n").toUtf8());
    }
}
