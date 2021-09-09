#include "xq/xqServer.hpp"
#include "xq/xqKernelModule.hpp"

// STL includes
#include <memory>
#include <thread>

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
  m_pollTimer = new QTimer();
  m_pollTimer->setInterval(10);
  QObject::connect(m_pollTimer, &QTimer::timeout, [=]() { poll(0); });
}

xqServer::~xqServer()
{
  m_pollTimer->stop();
  delete m_pollTimer;
}

void xqServer::start_impl(zmq::multipart_t& message)
{
    qDebug() << "Starting Jupyter kernel server";

    start_publisher_thread();
    start_heartbeat_thread();

    m_request_stop = false;

    m_pollTimer->start();

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
  xqKernelModule* kernelModule;
  if (kernelModule)
  {
    kernelModule->stopKernel();
  }
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
