#include "xq/xqQtPoller.hpp"

#include "xeus/xserver_zmq.hpp"
#include "xeus/xzmq_serializer.hpp"
#include "xeus/xmiddleware.hpp"

// zmq includes
#include <zmq_addon.hpp>

//this thread can never outlive the server thread... cause these sockets should be destroyed there and that
//would leave us with some hanging refs
WorkerThread::WorkerThread(QObject* parent,
                           zmq::context_t& context,
                           const xeus::xconfiguration& config,
                           xeus::xauthentication * auth,
                           bool * request_stop)
    : 
    QThread(parent),
    m_shell(context, zmq::socket_type::router),
    m_controller(context, zmq::socket_type::router)
{

    std::cout<<"INIT SOCKETS!\n";
    xeus::init_socket(m_shell, config.m_transport, config.m_ip, config.m_shell_port);
    xeus::init_socket(m_controller, config.m_transport, config.m_ip, config.m_control_port);
    p_auth = auth;
    p_request_stop = request_stop;
}

void WorkerThread::run()
{
    zmq::pollitem_t items[]
        = { { m_controller, 0, ZMQ_POLLIN, 0 }, { m_shell, 0, ZMQ_POLLIN, 0 } };

    while(true)
    {        
        std::cout<<"polling...\n";
        // timeout = -1, 
        // i should write a condition to end this while, dunno what yet, i think it should be the emits, so i can just break?
        

        std::cout<<"POLL\n";
        zmq::poll(&items[0], 2, -1);
        std::cout<<"POLL DONE\n";
        try
        {
            if (items[0].revents & ZMQ_POLLIN)
            {
                zmq::multipart_t * wire_msg = new zmq::multipart_t();
                wire_msg->recv(m_controller);
                // xeus::xmessage msg = xeus::xzmq_serializer::deserialize(wire_msg, *p_auth);
                emit resultReadyControl(wire_msg);
            }

            if (! (*p_request_stop) && (items[1].revents & ZMQ_POLLIN))
            {
                zmq::multipart_t * wire_msg = new zmq::multipart_t(); 
                wire_msg->recv(m_shell);
                // xeus::xmessage msg = xeus::xzmq_serializer::deserialize(wire_msg, *p_auth);
                
                emit resultReadyShell(wire_msg);
            }
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}
