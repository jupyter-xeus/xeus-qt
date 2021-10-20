#ifndef XQ_POLLER_HPP
#define XQ_POLLER_HPP


#include "zmq.hpp"
#include "zmq_addon.hpp"

#include <xeus/xmessage.hpp>
#include <iostream>

#include <QThread>

class WorkerThread : public QThread
{
    public:
        Q_OBJECT
        WorkerThread(QObject* parent, zmq::socket_t shell,
                     zmq::socket_t controller,
                     std::unique_ptr<xeus::xauthentication> auth,
                     bool request_stop);
        void run();
    protected:
        zmq::socket_t* m_shell;
        zmq::socket_t* m_controller;
        std::unique_ptr<xeus::xauthentication>* p_auth;
        bool *m_request_stop;
signals:
    void resultReadyControl(xeus::xmessage &s);
    void resultReadyShell(xeus::xmessage &s);
};

#endif