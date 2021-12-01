#ifndef XQ_POLLER_HPP
#define XQ_POLLER_HPP


#include "zmq.hpp"
#include "zmq_addon.hpp"

#include "xeus/xmessage.hpp"
#include "xeus/xauthentication.hpp"
#include "xeus/xkernel_configuration.hpp"

#include <iostream>

#include <QThread>
#include <QSharedData>


class WorkerThread : public QThread
{
    public:
        Q_OBJECT
    public:
        WorkerThread(QObject* parent, 
                     zmq::context_t& context,
                     const xeus::xconfiguration& config,
                     xeus::xauthentication * p_auth,
                     bool * request_stop);
        void run();
    protected:
        zmq::socket_t m_shell;
        zmq::socket_t m_controller;
        xeus::xauthentication *p_auth;
        bool* p_request_stop;
signals:
    // void resultReadyControl(xeus::xmessage &s);
    // void resultReadyShell(xeus::xmessage &s);

    void resultReadyControl(zmq::multipart_t * wire_msg);
    void resultReadyShell(zmq::multipart_t * wire_msg);
};

#endif