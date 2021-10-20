#include "xq/xqServer.hpp"
#include "xq/xqQtPoller.hpp"

// STL includes
#include <memory>
#include <thread>
#include <iostream>

// zmq includes
#include <zmq_addon.hpp>

// xeus includes
#include <xeus/xserver_zmq.hpp>
#include "xeus/xzmq_serializer.hpp"

// Qt includes
#include <QDebug>
#include <QTimer>

xqServer::xqServer(zmq::context_t& context,
                   const xeus::xconfiguration& c,
                   nl::json::error_handler_t eh)
    : xserver_zmq(context, c, eh)
{
    // 10ms interval is short enough so that users will not notice significant latency
    // yet it is long enough to minimize CPU load caused by polling.
    // 50ms causes too long delay in interactive widgets that handle mousemove events.
    // m_pollTimer = new QTimer();
    // m_pollTimer->setInterval(10);
    // QObject::connect(m_pollTimer, &QTimer::timeout, [=]() { poll(0); });
    // std::cout << "initializing the server" << std::endl;
}

xqServer::~xqServer()
{
    std::cout << "destroying the server" << std::endl;
    m_pollTimer->stop();
    delete m_pollTimer;
}

void xqServer::start_impl(xeus::xpub_message message)
{
    start_publisher_thread();
    start_heartbeat_thread();

    m_request_stop = false;

    m_pollTimer->start();

    startWorkInAThread();

    publish(std::move(message), xeus::channel::SHELL);

    // while (!m_request_stop)
    // {
    //     poll(-1);
    // }

    //     stop_channels();

    //     std::exit(0);
}

void xqServer::stop_impl()
{
    this->xserver_zmq::stop_impl();
    m_pollTimer->stop();
    stop_channels();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

// void xqServer::start_impl(xeus::xpub_message message)
// {
//     std::cout << "start_impl" << std::endl;
//     start_publisher_thread();
//     start_heartbeat_thread();

//     m_request_stop = false;

//     m_pollTimer->start();

//     publish(std::move(message), xeus::channel::SHELL);

    // while (!m_request_stop)
    // {
    //     poll(-1);
    // }

//     stop_channels();

//     // std::exit(0);
// }

// void xqServer::stop_impl()
// {
//     std::cout << "stop_impl" << std::endl;
//     this->xserver_zmq::stop_impl();
//     m_pollTimer->stop();
//     // stop_channels();
//     // std::this_thread::sleep_for(std::chrono::milliseconds(50));
// }

std::unique_ptr<xeus::xserver> make_xqServer(xeus::xcontext& context,
                                             const xeus::xconfiguration& config,
                                             nl::json::error_handler_t eh)
{
    std::cout << "making xqServer" << std::endl;
    return std::make_unique<xqServer>(context.get_wrapped_context<zmq::context_t>(), config, eh);
}

void xqServer::setPollIntervalSec(double intervalSec)
{
    m_pollTimer->setInterval(intervalSec*1000.0);
}

double xqServer::pollIntervalSec()
{
    return m_pollTimer->interval() / 1000.0;
}

// void xqServer::poll(long timeout) {
//     std::cout << "🔥" << std::endl;
// };


// void xqServer::poll(long timeout)
// {
//     // std::cout << "🍉" << std::endl;
//     zmq::pollitem_t items[]
//         = { { m_controller, 0, ZMQ_POLLIN, 0 }, { m_shell, 0, ZMQ_POLLIN, 0 } };

//     zmq::poll(&items[0], 2, std::chrono::milliseconds(timeout));

//     try
//     {
//         if (items[0].revents & ZMQ_POLLIN)
//         {
//             zmq::multipart_t wire_msg;
//             wire_msg.recv(m_controller);
//             xeus::xmessage msg = xeus::xzmq_serializer::deserialize(wire_msg, *p_auth);
//             // xeus::xserver::notify_control_listener(std::move(msg));
//         }

//         if (!m_request_stop && (items[1].revents & ZMQ_POLLIN))
//         {
//             zmq::multipart_t wire_msg;
//             wire_msg.recv(m_shell);
//             xeus::xmessage msg = xeus::xzmq_serializer::deserialize(wire_msg, *p_auth);
//             // xeus::xserver::notify_shell_listener(std::move(msg));
//         }
//     }
//     catch (std::exception& e)
//     {
//         std::cerr << e.what() << std::endl;
//     }
// }

void xqServer::startWorkInAThread()
{
    WorkerThread *workerThread = new WorkerThread(this,
                                                  m_shell,
                                                  m_controller,
                                                  p_auth,
                                                  m_request_stop);
    connect(workerThread, &WorkerThread::resultReadyControl, this, &xqServer::notify_control_listener);
    connect(workerThread, &WorkerThread::resultReadyShell, this, &xqServer::notify_shell_listener);
    workerThread->start();
}

void xqServer::notify_control_listener(xeus::xmessage msg)
{
    xeus::xserver::notify_control_listener(std::move(msg));
}

void xqServer::notify_shell_listener(xeus::xmessage msg)
{
    xeus::xserver::notify_shell_listener(std::move(msg));
}
