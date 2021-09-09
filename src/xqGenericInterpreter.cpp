#include <iostream>

#include "xq/xqGenericInterpreter.hpp"

#include <xeus/xguid.hpp>

xqGenericInterpreter::xqGenericInterpreter()
{
  std::cout << "started the interpreter 🌸\n";
}

void xqGenericInterpreter::set_jupyter_kernel_module(xqKernelModule* module)
{
  m_jupyter_kernel_module = module;
}
