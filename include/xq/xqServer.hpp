#ifndef XQ_SERVER_UTILS_HPP
#define XQ_SERVER_UTILS_HPP

#include <iostream>

#include "zmq.hpp"
#include "zmq_addon.hpp"

// xeus includes
#include <xeus/xmessage.hpp>
#include <xeus/xserver_zmq.hpp>
#include <xeus/xkernel_configuration.hpp>

// xqseme includes
#include "xq/xqQtPoller.hpp"

// Qt includes
#include <QList>
#include <QSharedPointer>
#include <QSocketNotifier>
#include <QSharedData>



class QTimer;





class xqServer : public xeus::xserver_zmq, public QObject
{

public:
    using socket_notifier_ptr = QSharedPointer<QSocketNotifier>;

    xqServer(zmq::context_t& context,
             const xeus::xconfiguration& config,
             nl::json::error_handler_t eh);
    virtual ~xqServer();

    // void setPollIntervalSec(double intervalSec);
    // double pollIntervalSec();

protected:
    void start_impl(xeus::xpub_message message) override;
    void stop_impl() override;
    void poll(long timeout);
    QTimer* m_pollTimer;

protected slots:
    void notify_control_listener(zmq::multipart_t * wire_msg);
    void notify_shell_listener(zmq::multipart_t * wire_msg);

    void startWorkInAThread();
private:
    WorkerThread * p_worker_thread;
};

std::unique_ptr<xeus::xserver> make_xqServer(xeus::xcontext& context,
                                             const xeus::xconfiguration& config,
                                             nl::json::error_handler_t eh);

#endif