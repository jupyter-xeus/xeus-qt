#ifndef XQ_SERVER_UTILS_HPP
#define XQ_SERVER_UTILS_HPP

#include <iostream>

#include "zmq.hpp"
#include "zmq_addon.hpp"

// xeus includes
#include <xeus/xmessage.hpp>
#include <xeus/xserver_zmq.hpp>
#include <xeus/xkernel_configuration.hpp>

// Qt includes
#include <QList>
#include <QSharedPointer>
#include <QSocketNotifier>

class QTimer;

class xqServer : public xeus::xserver_zmq, public QObject
{

public:
    using socket_notifier_ptr = QSharedPointer<QSocketNotifier>;

    xqServer(zmq::context_t& context,
             const xeus::xconfiguration& config,
             nl::json::error_handler_t eh);
    virtual ~xqServer();

    void setPollIntervalSec(double intervalSec);
    double pollIntervalSec();

protected:
    void start_impl(xeus::xpub_message message) override;
    void stop_impl() override;
    void poll(long timeout);
    QTimer* m_pollTimer;
protected slots:
    void notify_control_listener(xeus::xmessage msg);
    void notify_shell_listener(xeus::xmessage msg);
    void startWorkInAThread();
};

std::unique_ptr<xeus::xserver> make_xqServer(xeus::xcontext& context,
                                             const xeus::xconfiguration& config,
                                             nl::json::error_handler_t eh);

#endif