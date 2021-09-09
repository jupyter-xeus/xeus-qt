#ifndef XQ_GENERIC_INTERPRETER_HPP
#define XQ_GENERIC_INTERPRETER_HPP

#include "xq/xqKernelModule.hpp"

#include <xeus/xinterpreter.hpp>

class xqGenericInterpreter : public xeus::xinterpreter
{

public:

    xqGenericInterpreter();
    virtual ~xqGenericInterpreter() = default;

    void set_jupyter_kernel_module(xqKernelModule* module);

private:
    void configure_impl() override;

    nl::json execute_request_impl(int execution_counter,
                               const std::string& code,
                               bool store_history,
                               bool silent,
                               nl::json user_expressions,
                               bool allow_stdin) override;

    nl::json complete_request_impl(const std::string& code,
                                int cursor_pos) override;

    nl::json inspect_request_impl(const std::string& code,
                               int cursor_pos,
                               int detail_level) override;

    nl::json is_complete_request_impl(const std::string& code) override;

    nl::json kernel_info_request_impl() override;

    void shutdown_request_impl() override;

    xqKernelModule* m_jupyter_kernel_module = nullptr;
};

#endif
