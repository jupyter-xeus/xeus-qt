#ifndef XQ_POLLER_HPP
#define XQ_POLLER_HPP


#include "zmq.hpp"
#include "zmq_addon.hpp"

#include "xeus/xmessage.hpp"
#include "xeus/xauthentication.hpp"
#include "xeus/xkernel_configuration.hpp"

#include <iostream>
#include <atomic>

#include <QThread>
#include <QSharedData>


class WorkerThread : public QThread
{
    public:
        Q_OBJECT
    public:

        WorkerThread(QObject* parent,
                     zmq::socket_t* p_shell,
                     zmq::socket_t* p_controller,
                     xeus::xauthentication* p_auth);
        void run();
        void stop();
    protected:
        zmq::socket_t m_shell;
        zmq::socket_t m_controller;
        zmq::socket_t* p_shell;
        zmq::socket_t* p_controller;
        xeus::xauthentication* p_auth;
        std::atomic<bool> m_request_stop;

signals:
    void received_shell_msg_signal(xeus::xmessage* msg);
    void received_controll_msg_signal(xeus::xmessage* msg);
};

#endif