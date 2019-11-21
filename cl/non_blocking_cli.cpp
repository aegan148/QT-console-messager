#include <QTextStream>
#include <QDebug>

#include "non_blocking_cli.h"

NonBlockingCLI::NonBlockingCLI(QObject* parent) : QObject(parent) {
    this->moveToThread(&thread_); // создание потока

    connect(&thread_, &QThread::started, this, &NonBlockingCLI::read_stdin);

    thread_.start();
}

void NonBlockingCLI::read_stdin() { // записть смс
    QTextStream cin(stdin);
    QString line;

    while (cin.readLineInto(&line))
    {
        emit line_is_read(line);

    }
}
