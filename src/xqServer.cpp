#include "xq/xqServer.hpp"
#include "xq/xqKernelModule.hpp"

// STL includes
#include <memory>
#include <thread>
#include <iostream>

// zmq includes
#include <zmq_addon.hpp>

// xeus includes
#include <xeus/xserver_zmq.hpp>

// Qt includes
#include <QDebug>
#include <QTimer>

xqServer::xqServer(zmq::context_t& context,
                   const xeus::xconfiguration& c)
    : xserver_zmq(context, c)
{
  // 10ms interval is short enough so that users will not notice significant latency
  // yet it is long enough to minimize CPU load caused by polling.
  // 50ms causes too long delay in interactive widgets that handle mousemove events.
  std::cout << "Entering constructor of xserver" << std::endl;
  m_pollTimer = new QTimer();
  m_pollTimer->setInterval(10);
  QObject::connect(m_pollTimer, &QTimer::timeout, [=]() { poll(0); });
  std::cout << "Exiting constructor of xserver"  << std::endl;
}

xqServer::~xqServer()
{
  m_pollTimer->stop();
  delete m_pollTimer;
}

void xqServer::start_impl(zmq::multipart_t& message)
{
    // qDebug() << "Starting Jupyter kernel server";
    std::cout << "Starting Jupyter kernel server" << std::endl;

    start_publisher_thread();
    start_heartbeat_thread();

    //this shouldn't be here? how are stuff called
    // xqKernelModule* kernelModule;
    // kernelModule->startKernel();

    m_request_stop = false;

    std::cout << "Starting polltimer" << std::endl;
    m_pollTimer->start();
    std::cout << "After starting polltimer" << std::endl;

    publish(message, xeus::channel::SHELL);
}

void xqServer::stop_impl()
{
  qDebug() << "Stopping Jupyter kernel server";
  this->xserver_zmq::stop_impl();
  m_pollTimer->stop();
  stop_channels();
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // Notify JupyterKernel module about kernel stop.
  //// qSlicerCoreApplication::application()->moduleManager()->module("JupyterKernel")
  //this is not gonna work?!?

  //is kernel module a static thing?
  // xqKernelModule* kernelModule;
  // if (kernelModule)
  // {
  //   kernelModule->stopKernel();
  // }
  //this should do this:
  //  Q_D(qSlicerJupyterKernelModule);
  // Kernel shutdown requested
  // emit kernelStopRequested();
  // if (d->StatusLabel)
  // {
  //   d->StatusLabel->setText("");
  // }
  // qSlicerApplication::application()->exit(0);
  //i wonder if I should receive this app, or maybe only some kind of signal slot thing would work for this
  //i could emit a signal here that eventually closes the app in a common class for both, but
  //if the app is a singleton then it's fine and I don't even need to do anything, 
  //just call it here, but I don't think it is... doesn't make sense, I have to receive it smh, or make a class
}

std::unique_ptr<xeus::xserver> make_xqServer(zmq::context_t& context,
                                             const xeus::xconfiguration& config)
{
    return std::make_unique<xqServer>(context, config);
}

void xqServer::setPollIntervalSec(double intervalSec)
{
  m_pollTimer->setInterval(intervalSec*1000.0);
}

double xqServer::pollIntervalSec()
{
  return m_pollTimer->interval() / 1000.0;
}
