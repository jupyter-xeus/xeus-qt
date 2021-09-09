// JupyterKernel includes
#include "xq/xqKernelModule.hpp"
//I need to have both these things with APIs that interact with this code to be able to do this
#include "xq/xqGenericApplication.hpp"
#include "xq/xqGenericInterpreter.hpp"
#include "xq/xqServer.hpp"

// XEUS includes
#include "xeus/xkernel.hpp"
#include "xeus/xkernel_configuration.hpp"

// Qt includes
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QLabel>
#include <QMainWindow>
#include <QProcess>
#include <QStandardPaths>
#include <QStatusBar>
#include <QTextStream>

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class xqKernelModulePrivate
{
protected:
  xqKernelModule * const q_ptr;

public:
  xqKernelModulePrivate(xqKernelModule& object);

  // QProcess InternalJupyterServer;
  bool Started;
  QString ConnectionFile;
  xeus::xkernel * Kernel;
  xeus::xconfiguration Config;
  QLabel* StatusLabel;
};

//-----------------------------------------------------------------------------
// xqKernelModulePrivate methods

//-----------------------------------------------------------------------------
xqKernelModulePrivate::xqKernelModulePrivate(xqKernelModule& object)
: q_ptr(&object)
, Started(false)
, Kernel(NULL)
, StatusLabel(NULL)
{
}

//-----------------------------------------------------------------------------
// xqKernelModule methods

//-----------------------------------------------------------------------------
xqKernelModule::xqKernelModule()
  : d_ptr(new xqKernelModulePrivate(*this))
{
}

//-----------------------------------------------------------------------------
void xqKernelModule::startKernel(const QString& connectionFile)
{
  Q_D(xqKernelModule);
  d->ConnectionFile = connectionFile;
  if (!QFileInfo::exists(connectionFile))
  {
    qWarning() << "startKernel" << "connectionFile does not exist" << connectionFile;
    return;
  }
  if (d->Started)
  {
    qWarning() << "Kernel already started";
  }
  else
  {
    d->Config = xeus::load_configuration(connectionFile.toStdString());

    //i should just receive an extensible thing here too? I think it
    //should be some kind of function argument actually
    //then how do I get a type for this...
    using interpreter_ptr = std::unique_ptr<xqGenericInterpreter>;
    interpreter_ptr interpreter = interpreter_ptr(new xqGenericInterpreter());
    //I think I need to extend the interpreter to have smth like this
    // void xSlicerxqGenericInterpreter::set_jupyter_kernel_module(qSlicerJupyterKernelModule* module)
    // {
    //   m_jupyter_kernel_module = module;
    // }
    //qSlicerJupyterKernelModule* m_jupyter_kernel_module = nullptr;
    //but maybe not, maybe this is just a python thing
    interpreter->set_jupyter_kernel_module(this);

    using history_manager_ptr = std::unique_ptr<xeus::xhistory_manager>;
    history_manager_ptr hist = xeus::make_in_memory_history_manager();

    d->Kernel = new xeus::xkernel(d->Config,
                                  "slicer",
                                  std::move(interpreter),
                                  std::move(hist),
                                  nullptr,
                                  make_xqServer);

    d->Kernel->start();

    d->Started = true;

    QStatusBar* statusBar = NULL;
    //we shouldn't force users to have GUIs
    // if (xqGenericApplication::application()->mainWindow())
    // {
    //   statusBar = xqGenericApplication::application()->mainWindow()->statusBar();
    // }
    // if (statusBar)
    // {
    //   if (!d->StatusLabel)
    //   {
    //     d->StatusLabel = new QLabel;
    //     statusBar->insertPermanentWidget(0, d->StatusLabel);
    //   }
    //   d->StatusLabel->setText(tr("<b><font color=\"red\">Application is managed by Jupyter</font></b>"));
    // }
    emit kernelStarted();
  }
}

//-----------------------------------------------------------------------------
void xqKernelModule::stopKernel()
{
  Q_D(xqKernelModule);
  // Kernel shutdown requested
  emit kernelStopRequested();
  if (d->StatusLabel)
  {
    d->StatusLabel->setText("");
  }
  xqGenericApplication::application()->exit(0);
}


//---------------------------------------------------------------------------
double xqKernelModule::pollIntervalSec()
{
  Q_D(xqKernelModule);
  if (d->Kernel == nullptr)
  {
    qCritical() << Q_FUNC_INFO << " failed: kernel has not started yet";
    return 0.0;
  }
  return reinterpret_cast<xqServer*>(&d->Kernel->get_server())->pollIntervalSec();

  return 0.0;
}

//---------------------------------------------------------------------------
QString xqKernelModule::connectionFile()
{
  Q_D(xqKernelModule);
  return d->ConnectionFile;
}

//---------------------------------------------------------------------------
void xqKernelModule::setPollIntervalSec(double intervalSec)
{
  Q_D(xqKernelModule);
  if (d->Kernel == nullptr)
  {
    qCritical() << Q_FUNC_INFO << " failed: kernel has not started yet";
    return;
  }

  reinterpret_cast<xqServer*>(&d->Kernel->get_server())->setPollIntervalSec(intervalSec);
}
