/***************************************************************************
* Copyright (c) 2021, QuantStack                                           *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XQ_POLLER_HPP
#define XQ_POLLER_HPP

#include <atomic>
#include <functional>
#include <optional>

#include <QThread>
#include <QSharedData>

#include "xeus/xserver.hpp"

#include "xq.hpp"

namespace xeus
{
    class XQ_API WorkerThread : public QThread
    {
    public:

        Q_OBJECT

    public:

        using message_channel = std::pair<xmessage, channel>;
        using opt_message_channel = std::optional<message_channel>;
        using poller_t = std::function<opt_message_channel(long)>;

        WorkerThread(QObject* parent,
                     poller_t poller);

        void run();
        void stop();

    private:

        poller_t m_poller;
        std::atomic<bool> m_request_stop;

    signals:

        void received_shell_msg_signal(xeus::xmessage* msg);
        void received_controll_msg_signal(xeus::xmessage* msg);
    };
}

#endif

