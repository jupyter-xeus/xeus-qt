#ifndef XQ_SERVER_UTILS_HPP
#define XQ_SERVER_UTILS_HPP

#include <iostream>

// xeus includes
#include <xeus/xserver_zmq.hpp>
#include <xeus/xkernel_configuration.hpp>

// Qt includes
#include <QList>
#include <QSharedPointer>
#include <QSocketNotifier>

class QTimer;

class xqServer : public xeus::xserver_zmq
{

public:
    using socket_notifier_ptr = QSharedPointer<QSocketNotifier>;

    xqServer(zmq::context_t& context,
             const xeus::xconfiguration& config);
    virtual ~xqServer();

    void setPollIntervalSec(double intervalSec);
    double pollIntervalSec();

protected:

    void start_impl(zmq::multipart_t& message) override;
    void stop_impl() override;
    QTimer* m_pollTimer;
};

std::unique_ptr<xeus::xserver> make_xqServer(zmq::context_t& context,
                                             const xeus::xconfiguration& config);



#endif