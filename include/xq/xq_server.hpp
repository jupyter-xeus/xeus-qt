/***************************************************************************
* Copyright (c) 2021, QuantStack                                           *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XQ_SERVER_UTILS_HPP
#define XQ_SERVER_UTILS_HPP

#include "xeus-zmq/xserver_zmq.hpp"

#include "xq.hpp"
#include "xq_qt_poller.hpp"

namespace xeus
{
    class XQ_API xq_server : public xeus::xserver_zmq, public QObject
    {
    public:

        xq_server(xcontext& context,
                 const xconfiguration& config,
                 nl::json::error_handler_t eh);

        ~xq_server() override = default;

    private:

        void start_impl(xpub_message message) override;
        void stop_impl() override;
        void start_poller_qthread();

        WorkerThread m_worker_thread;

    private slots:

        void on_received_shell_msg(xeus::xmessage* msg);
        void on_received_controll_msg(xeus::xmessage* msg);
    };

    XQ_API
    std::unique_ptr<xserver> make_xq_server(xcontext& context,
                                            const xconfiguration& config,
                                            nl::json::error_handler_t eh);
}

#endif

