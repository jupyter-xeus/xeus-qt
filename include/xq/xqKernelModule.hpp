#ifndef XQ_KERNEL_MODULE_HPP
#define XQ_KERNEL_MODULE_HPP

#include <QObject>

#include "xeus/xkernel.hpp"

class xqKernelModulePrivate;

class xqKernelModule : public QObject
{
  Q_OBJECT
public:

  xqKernelModule();
  virtual ~xqKernelModule();

  double pollIntervalSec();

  QString connectionFile();

  xeus::xkernel* Kernel;

public slots:

  void startKernel();
  void stopKernel();
  void setPollIntervalSec(double intervalSec);

signals:
  // Called after kernel has successfully started
  void kernelStarted();

  // Called when Jupyter requested stopping of the kernel.
  void kernelStopRequested();
};

#endif
