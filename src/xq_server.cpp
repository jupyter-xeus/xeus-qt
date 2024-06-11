/***************************************************************************
* Copyright (c) 2021, QuantStack                                           *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "xq/xq_server.hpp"
#include "xq/xq_qt_poller.hpp"

namespace xeus
{
    xq_server::xq_server(xcontext& context,
                         const xeus::xconfiguration& c,
                         nl::json::error_handler_t eh)
        : xserver_zmq(context, c, eh)
        , m_worker_thread(this, [this](long timeout) {
                return poll_channels(timeout); })
    {
    }

    void xq_server::start_impl(xpub_message message)
    {
        start_publisher_thread();
        start_heartbeat_thread();

        publish(std::move(message), xeus::channel::SHELL);

        start_poller_qthread();
    }

    void xq_server::stop_impl()
    {
        m_worker_thread.stop();
        m_worker_thread.wait();
        this->stop_channels();
    }

    void xq_server::start_poller_qthread()
    {
        connect(&m_worker_thread, &WorkerThread::received_shell_msg_signal, this, &xq_server::on_received_shell_msg);
        connect(&m_worker_thread, &WorkerThread::received_controll_msg_signal, this, &xq_server::on_received_controll_msg);
        m_worker_thread.start();
    }

    void xq_server::on_received_controll_msg(xmessage * pmsg)
    {
        xmessage msg(std::move(*pmsg));
        xserver::notify_control_listener(std::move(msg));
        delete pmsg;
    }

    void xq_server::on_received_shell_msg(xmessage * pmsg)
    {
        xmessage msg( std::move(*pmsg));
        xserver::notify_shell_listener(std::move(msg));
        delete pmsg;
    }

    std::unique_ptr<xserver> make_xq_server(xcontext& context,
                                            const xeus::xconfiguration& config,
                                            nl::json::error_handler_t eh)
    {
        return std::make_unique<xq_server>(context, config, eh);
    }
}

