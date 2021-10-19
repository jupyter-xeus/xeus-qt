#include "xq/xqQtPoller.hpp"

WorkerThread::WorkerThread(QObject* parent, zmq::socket_t shell, zmq::socket_t controller)
    : QThread(parent)
{
    m_controller = controller;
    m_shell = shell;
}

void WorkerThread::run() override {
    zmq::pollitem_t items[]
        = { { m_controller, 0, ZMQ_POLLIN, 0 }, { m_shell, 0, ZMQ_POLLIN, 0 } };

    while(true)
    {        // timeout
    zmq::poll(&items[0], 2, -1);

    try
    {
        if (items[0].revents & ZMQ_POLLIN)
        {
            zmq::multipart_t wire_msg;
            wire_msg.recv(m_controller);
            xeus::xmessage msg = xeus::xzmq_serializer::deserialize(wire_msg, *p_auth);
            emit resultReadyControl(msg);
        }

        if (!m_request_stop && (items[1].revents & ZMQ_POLLIN))
        {
            zmq::multipart_t wire_msg;
            wire_msg.recv(m_shell);
            xeus::xmessage msg = xeus::xzmq_serializer::deserialize(wire_msg, *p_auth);
            emit resultReadyShell(msg);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    }
}
