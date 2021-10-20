#include "xq/xqQtPoller.hpp"

#include "xeus/xserver_zmq.hpp"
#include "xeus/xzmq_serializer.hpp"


//this thread can never outlive the server thread... cause these sockets should be destroyed there and that
//would leave us with some hanging refs
WorkerThread::WorkerThread(QObject* parent,
                           zmq::socket_t shell,
                           zmq::socket_t controller,
                           std::unique_ptr<xeus::xauthentication> auth,
                           bool request_stop)
    : QThread(parent)
{
    m_controller = &controller;
    m_shell = &shell;
    p_auth = &auth;
    m_request_stop = &request_stop;
}

void WorkerThread::run()
{
    zmq::pollitem_t items[]
        = { { m_controller, 0, ZMQ_POLLIN, 0 }, { m_shell, 0, ZMQ_POLLIN, 0 } };

    while(true)
    {        // timeout = -1, 
            //i should write a condition to end this while, dunno what yet, i think it should be the emits, so i can just break?
    zmq::poll(&items[0], 2, -1);

    try
    {
        if (items[0].revents & ZMQ_POLLIN)
        {
            zmq::multipart_t wire_msg;
            wire_msg.recv(*m_controller);
            xeus::xmessage msg = xeus::xzmq_serializer::deserialize(wire_msg, **p_auth);
            emit resultReadyControl(msg);
        }

        if (!m_request_stop && (items[1].revents & ZMQ_POLLIN))
        {
            zmq::multipart_t wire_msg;
            wire_msg.recv(*m_shell);
            xeus::xmessage msg = xeus::xzmq_serializer::deserialize(wire_msg, **p_auth);
            emit resultReadyShell(msg);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    }
}
