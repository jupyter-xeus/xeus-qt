/***************************************************************************
* Copyright (c) 2021, QuantStack                                           *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include <iostream>

#include "xq/xq_qt_poller.hpp"

namespace xeus
{

    WorkerThread::WorkerThread(QObject* parent,
                               poller_t poller)
        : QThread(parent)
        , m_poller(std::move(poller))
        , m_request_stop(false)
    {
        std::cout << "starting thread" << std::endl;
    }

    void WorkerThread::run()
    {
        while(!m_request_stop.load())
        {
            auto msg = m_poller(10);
            if (msg)
            {
                if (msg.value().second == channel::SHELL)
                {
                    // signals do not like the move semantics so
                    // we need to put in a pointer and delete it on the receiving end
                    xeus::xmessage* pmsg = new xeus::xmessage(std::move(msg.value().first));
                    emit received_shell_msg_signal(pmsg);
                }
                else
                {
                    // signals do not like the move semantics so
                    // we need to put in a pointer and delete it on the receiving end
                    xeus::xmessage* pmsg = new xeus::xmessage(std::move(msg.value().first));
                    emit received_controll_msg_signal(pmsg);
                }
            }
        }
    }

    void WorkerThread::stop()
    {
        m_request_stop = true;
    }
}

