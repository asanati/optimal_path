#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QString>
#include "mainwindow.h"

class MyThread : public QThread {
public:
    explicit MyThread(QString s, MainWindow* w, Vector2d startingPos, Vector2d endingPos);
    void run();

private:
    QString name;
    MainWindow* w;
    Vector2d startingPos, endingPos;
};

#endif // MYTHREAD_H
