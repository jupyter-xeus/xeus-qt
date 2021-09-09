#include "xq/xqGenericApplication.hpp"

xqGenericApplication::xqGenericApplication(int &argc, char **argv)
  : QCoreApplication(argc, argv)
{
  // Note: You are responsible to call init() in the constructor of derived class.
}

xqGenericApplication* xqGenericApplication::application()
{
  xqGenericApplication* app = qobject_cast<xqGenericApplication*>(QCoreApplication::instance());
  return app;
}
