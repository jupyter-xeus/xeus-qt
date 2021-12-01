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
    : xserver_zmq(context, c, eh),
      p_worker_thread(new WorkerThread(this, context, c, p_auth.get(), &m_request_stop))
{
    std::cout<<"USED CORRECT CONSTRCTOR\n";
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
    std::cout<<"start publisher thread\n";
    start_publisher_thread();

    std::cout<<"start hearbeat thread\n";
    start_heartbeat_thread();

    m_request_stop = false;

    std::cout<<"start m_pollTimer\n";
    //m_pollTimer->start();


    publish(std::move(message), xeus::channel::SHELL);
    std::cout<<"published\n";


    std::cout<<"startWorkInAThread\n";
    startWorkInAThread();
    std::cout<<"startedWorkInAThread\n";



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


std::unique_ptr<xeus::xserver> make_xqServer(xeus::xcontext& context,
                                             const xeus::xconfiguration& config,
                                             nl::json::error_handler_t eh)
{
    std::cout << "making xqServer" << std::endl;
    return std::make_unique<xqServer>(context.get_wrapped_context<zmq::context_t>(), config, eh);
}


void xqServer::startWorkInAThread()
{
    // WorkerThread *workerThread = new WorkerThread(this,
    //                                               &m_shell,
    //                                               &m_controller,
    //                                               p_auth.get(),
    //                                               &m_request_stop);
    // p_worker_thread
    connect(p_worker_thread, &WorkerThread::resultReadyControl, this, &xqServer::notify_control_listener);
    connect(p_worker_thread, &WorkerThread::resultReadyShell, this, &xqServer::notify_shell_listener);
    p_worker_thread->start();
}


void xqServer::notify_control_listener(zmq::multipart_t * wire_msg)
{
    xeus::xmessage msg = xeus::xzmq_serializer::deserialize(*wire_msg, *p_auth);
    xeus::xserver::notify_control_listener(std::move(msg));
    delete wire_msg;
}

void xqServer::notify_shell_listener(zmq::multipart_t * wire_msg)
{
    xeus::xmessage msg = xeus::xzmq_serializer::deserialize(*wire_msg, *p_auth);
    xeus::xserver::notify_shell_listener(std::move(msg));
    delete wire_msg;
}
