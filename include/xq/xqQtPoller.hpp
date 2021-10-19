#ifndef XQ_POLLER_HPP
#define XQ_POLLER_HPP
#include <xeus/xmessage.hpp>
#include <iostream>

#include <QThread>

class WorkerThread : public QThread
{
    Q_OBJECT
    WorkerThread();
    void run() override;
signals:
    void resultReadyControl(xeus::xmessage &s);
    void resultReadyShell(xeus::xmessage &s);
};

#endif