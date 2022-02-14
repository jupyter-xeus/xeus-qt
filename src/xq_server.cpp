#include <memory>
#include <thread>
#include <iostream>

#include <zmq_addon.hpp>

#include <xeus/xserver_zmq.hpp>
#include "xeus/xzmq_serializer.hpp"

#include "xq/xq_server.hpp"
#include "xq/xq_qt_poller.hpp"

#include <QDebug>
#include <QTimer>

xq_server::xq_server(zmq::context_t& context,
                     const xeus::xconfiguration& c,
                     nl::json::error_handler_t eh)
    :
    xserver_zmq(context, c, eh),
    m_worker_thread(this, &m_shell, &m_controller, p_auth.get())
{
}

void xq_server::start_impl(xeus::xpub_message message)
{
    start_publisher_thread();
    start_heartbeat_thread();

    publish(std::move(message), xeus::channel::SHELL);

    start_poller_qthread();
}

void xq_server::stop_impl()
{
    xserver_zmq::stop_impl();
    m_worker_thread.stop();
    m_worker_thread.wait();
    this->stop_channels();
}

std::unique_ptr<xeus::xserver> make_xq_server(xeus::xcontext& context,
                                              const xeus::xconfiguration& config,
                                              nl::json::error_handler_t eh)
{
    return std::make_unique<xq_server>(context.get_wrapped_context<zmq::context_t>(), config, eh);
}

void xq_server::start_poller_qthread()
{
    connect(&m_worker_thread, &WorkerThread::received_shell_msg_signal, this, &xq_server::on_received_shell_msg);
    connect(&m_worker_thread, &WorkerThread::received_controll_msg_signal, this, &xq_server::on_received_controll_msg);
    m_worker_thread.start();
}

void xq_server::on_received_controll_msg(xeus::xmessage * pmsg)
{
    xeus::xmessage msg(std::move(*pmsg));
    xeus::xserver::notify_control_listener(std::move(msg));
    delete pmsg;
}

void xq_server::on_received_shell_msg(xeus::xmessage * pmsg)
{
    xeus::xmessage msg( std::move(*pmsg));
    xeus::xserver::notify_shell_listener(std::move(msg));
    delete pmsg;
}
