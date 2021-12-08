#include "xq/xqQtPoller.hpp"


#include "xeus/xserver_zmq.hpp"
#include "xeus/xzmq_serializer.hpp"
#include "xeus/xmiddleware.hpp"

// zmq includes
#include <zmq_addon.hpp>



WorkerThread::WorkerThread(QObject* parent,
                           zmq::socket_t * p_shell,
                           zmq::socket_t * p_controller,
                           xeus::xauthentication * auth)
    : 
    QThread(parent),
    p_shell(p_shell),
    p_controller(p_controller),
    m_request_stop(false)
{

    p_auth = auth;
}
void WorkerThread::stop()
{   
    m_request_stop = true;  
}

void WorkerThread::run()
{
    zmq::pollitem_t items[]
        = { { *p_controller, 0, ZMQ_POLLIN, 0 }, { *p_shell, 0, ZMQ_POLLIN, 0 } };

    while(!m_request_stop.load())
    {        

        zmq::poll(&items[0], 2, std::chrono::milliseconds(10));
        {
            try{
                if (items[0].revents & ZMQ_POLLIN)
                {
                    zmq::multipart_t  wire_msg;
                    wire_msg.recv(*p_controller);
                    xeus::xmessage msg = xeus::xzmq_serializer::deserialize(wire_msg, *p_auth);

                    // signals do not like the move semantics so 
                    // we need to put in a pointer and delete it on the receiving end  
                    xeus::xmessage * pmsg = new xeus::xmessage(std::move(msg));
                    emit received_controll_msg_signal(pmsg);
                }

                if (! m_request_stop.load() && (items[1].revents & ZMQ_POLLIN))
                {
                    zmq::multipart_t  wire_msg;
                    wire_msg.recv(*p_shell);
                    xeus::xmessage msg = xeus::xzmq_serializer::deserialize(wire_msg, *p_auth);

                    // signals do not like the move semantics so 
                    // we need to put in a pointer and delete it on the receiving end  
                    xeus::xmessage * pmsg = new xeus::xmessage(std::move(msg));
                    emit received_shell_msg_signal(pmsg);
                }
            }
            catch (std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}
