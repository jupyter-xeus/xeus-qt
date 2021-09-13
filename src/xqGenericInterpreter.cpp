#include <iostream>

#include "xq/xqGenericInterpreter.hpp"

#include <xeus/xguid.hpp>

//i think this should be a template
//template <typename T>
// xqGenericInterpreter::xqGenericInterpreter(T interpreter)
xqGenericInterpreter::xqGenericInterpreter()
{
  std::cout << "xqGenericInterpreter starting...\n";
}

void xqGenericInterpreter::configure_impl()
{
}

nl::json xqGenericInterpreter::execute_request_impl(int execution_counter,
                                                    const std::string& code,
                                                    bool store_history,
                                                    bool silent,
                                                    nl::json user_expressions,
                                                    bool allow_stdin)
{
}

nl::json xqGenericInterpreter::complete_request_impl(const std::string& code,
                                                     int cursor_pos)
{
}

nl::json xqGenericInterpreter::inspect_request_impl(const std::string& code,
                                                    int cursor_pos,
                                                    int detail_level)
{
}

nl::json xqGenericInterpreter::is_complete_request_impl(const std::string& code)
{
}

nl::json xqGenericInterpreter::kernel_info_request_impl()
{
}

void xqGenericInterpreter::shutdown_request_impl()
{
}
