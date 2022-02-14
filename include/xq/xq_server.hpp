#ifndef XQ_SERVER_UTILS_HPP
#define XQ_SERVER_UTILS_HPP

#include <iostream>

#include "zmq.hpp"
#include "zmq_addon.hpp"

#include <xeus/xmessage.hpp>
#include <xeus/xserver_zmq.hpp>
#include <xeus/xkernel_configuration.hpp>

#include "xq/xq_qt_poller.hpp"

#include <QList>
#include <QSharedPointer>
#include <QSocketNotifier>
#include <QSharedData>


class xq_server : public xeus::xserver_zmq, public QObject
{

public:
    using socket_notifier_ptr = QSharedPointer<QSocketNotifier>;

    xq_server(zmq::context_t& context,
             const xeus::xconfiguration& config,
             nl::json::error_handler_t eh);
    virtual ~xq_server() = default;

protected:
    void start_impl(xeus::xpub_message message) override;
    void stop_impl() override;
    void start_poller_qthread();

protected slots:
    void on_received_shell_msg(xeus::xmessage* msg);
    void on_received_controll_msg(xeus::xmessage* msg);

private:
    WorkerThread m_worker_thread;
};

std::unique_ptr<xeus::xserver> make_xq_server(xeus::xcontext& context,
                                             const xeus::xconfiguration& config,
                                             nl::json::error_handler_t eh);

#endif