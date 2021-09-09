#ifndef XQ_KERNEL_MODULE_HPP
#define XQ_KERNEL_MODULE_HPP

#include <QObject>

class xqKernelModulePrivate;

class xqKernelModule : public QObject
{
  Q_OBJECT
public:

  xqKernelModule();
  virtual ~xqKernelModule();

  double pollIntervalSec();

  QString connectionFile();

public slots:

  void startKernel(const QString& connectionFile);
  void stopKernel();
  void setPollIntervalSec(double intervalSec);

signals:
  // Called after kernel has successfully started
  void kernelStarted();

  // Called when Jupyter requested stopping of the kernel.
  void kernelStopRequested();
protected:
  QScopedPointer<xqKernelModulePrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(xqKernelModule);
  Q_DISABLE_COPY(xqKernelModule);

};

#endif
