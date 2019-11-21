#include <QCoreApplication>
#include <QObject>
#include"hclient.h"
#include"non_blocking_cli.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream cin(stdin);
    QString name;
    qDebug()<<"Enter your name";
    name= cin.readLine();

    NonBlockingCLI cli;

    mClient clir;

    QObject::connect(&cli, &NonBlockingCLI::line_is_read, &clir, &mClient::message_entered);
    clir.sockStart(name);




    return a.exec();
}
