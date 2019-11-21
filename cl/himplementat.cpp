#include"hclient.h"

mClient::mClient(QObject* parent ):
    QObject(parent),
    socket (new QTcpSocket(this))

{
    connect (socket, &QTcpSocket::readyRead,this,&mClient::sockReady);
    connect (socket, &QTcpSocket::disconnected,this,&mClient::sockESC);
};

void mClient::sockStart(QString& name){ // старт с ожидание передачи имени
    Name=name;

   socket->connectToHost(QHostAddress::LocalHost, 3122);
}

void mClient::sockReady(){ // чтение

        Data= socket->readAll();//извлекаем дата
        QDebug debug = qDebug(); // без кавычек от дебага
        debug.noquote();
        debug<<Data;
}

void mClient::sockESC(){ // на выход
    qDebug()<<"Disconected";
    socket->deleteLater();

}
void mClient::message_entered(QString message) // запись стринга в сокет
{
    if (!message.isEmpty())
    {
        socket->write(QString(Name+ ": "+message + "\n").toUtf8());
    }
}

mClient::~mClient(){delete socket;};
