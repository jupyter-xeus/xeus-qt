#include <iostream>

// JupyterKernel includes
#include "xq/xqKernelModule.hpp"
//I need to have both these things with APIs that interact with this code to be able to do this
#include "xq/xqGenericApplication.hpp"
#include "xq/xqGenericInterpreter.hpp"
#include "xq/xqServer.hpp"

// XEUS includes
#include "xeus/xkernel.hpp"
#include "xeus/xkernel_configuration.hpp"

// // Qt includes
#include <QDebug>
#include <QFileInfo>

//-----------------------------------------------------------------------------
// xqKernelModule methods

//-----------------------------------------------------------------------------
xqKernelModule::xqKernelModule()
  : Kernel(NULL)
{
}

xqKernelModule::~xqKernelModule()
{}

//-----------------------------------------------------------------------------
void xqKernelModule::startKernel()
{
  std::cout << "startKernel from xqKernelModule" << std::endl;
  // this->Kernel->ConnectionFile = connectionFile;
  // if (!QFileInfo::exists(connectionFile))
  // {
  //   qWarning() << "startKernel" << "connectionFile does not exist" << connectionFile;
  //   return;
  // }
  // if (this->Kernel.Started)
  // {
  //   qWarning() << "Kernel already started";
  // }
  // else
  // {
  std::cout << "🌈 the kernel has started" << std::endl;
    // this->Kernel.Started = true;
    emit kernelStarted();
  // }
}

//-----------------------------------------------------------------------------
void xqKernelModule::stopKernel()
{
  emit kernelStopRequested();
  xqGenericApplication::application()->exit(0);
}

//---------------------------------------------------------------------------
double xqKernelModule::pollIntervalSec()
{
  if (this->Kernel == nullptr)
  {
    qCritical() << Q_FUNC_INFO << " failed: kernel has not started yet";
    return 0.0;
  }
  return reinterpret_cast<xqServer*>(&this->Kernel->get_server())->pollIntervalSec();

  return 0.0;
}

//---------------------------------------------------------------------------
QString xqKernelModule::connectionFile()
{
  // return this->Kernel.ConnectionFile;
}

//---------------------------------------------------------------------------
void xqKernelModule::setPollIntervalSec(double intervalSec)
{
  if (this->Kernel == nullptr)
  {
    qCritical() << Q_FUNC_INFO << " failed: kernel has not started yet";
    return;
  }

  reinterpret_cast<xqServer*>(&this->Kernel->get_server())->setPollIntervalSec(intervalSec);
}
