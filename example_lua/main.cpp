#include <iostream>
#include <fstream>

#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QString>

#include "xq/xqServer.hpp"
#include "xq/xqQtPoller.hpp"

#include "xeus/xkernel.hpp"
#include "xeus/xkernel_configuration.hpp"

#include "xeus-lua/xinterpreter.hpp"
#include "xeus-lua/xeus_lua_config.hpp"

void create_json_file(std::string kernel_info)
{
    
    std::ofstream kernel_json("kernel.json");
    kernel_json << kernel_info;
    kernel_json.close();
}

int main(int argc, char *argv[])
{
    // Create interpreter instance
    using interpreter_ptr = std::unique_ptr<xlua::interpreter>;
    interpreter_ptr interpreter = std::make_unique<xlua::interpreter>();

    // Create history instance
    using history_manager_ptr = std::unique_ptr<xeus::xhistory_manager>;
    history_manager_ptr hist = xeus::make_in_memory_history_manager();

    auto context = xeus::make_context<zmq::context_t>();

    // Create xkernel using a Qt compatible server
    std::cout<<"START KERNEL\n";
    xeus::xkernel kernel(xeus::get_user_name(),
                         std::move(context),
                         std::move(interpreter),
                         make_xqServer,
                         std::move(hist),
                         nullptr);

    std::cout<<"START DONE\n";
    const auto& config = kernel.get_config();

    std::string kernel_info, tutorial;
    tutorial = "Starting xeus-python kernel...\n\n"
                    "If you want to connect to this kernel from an other client, just copy"
                    " and paste the following content inside of a `kernel.json` file. And then run for example:\n\n"
                    "# jupyter console --existing kernel.json\n\n"
                    "kernel.json\n\n";
    kernel_info = "{\n"
                  "    \"transport\": \"" + config.m_transport + "\",\n"
                  "    \"ip\": \"" + config.m_ip + "\",\n"
                  "    \"control_port\": " + config.m_control_port + ",\n"
                  "    \"shell_port\": " + config.m_shell_port + ",\n"
                  "    \"stdin_port\": " + config.m_stdin_port + ",\n"
                  "    \"iopub_port\": " + config.m_iopub_port + ",\n"
                  "    \"hb_port\": " + config.m_hb_port + ",\n"
                  "    \"signature_scheme\": \"" + config.m_signature_scheme + "\",\n"
                  "    \"key\": \"" + config.m_key + "\"\n"
                  "}\n";

    std::cout<<"kernel info : "<<kernel_info<<"\n";
    std::cout<<"start qapp\n";


    QApplication application(argc, argv);
    kernel.start();


    std::cout<<"start kernel\n";
    std::cout<<"start kernel done\n";

    QMainWindow mainWindow;
    mainWindow.resize(320, 240);


    // Set layout
    QHBoxLayout *layout = new QHBoxLayout;
    // layout->addWidget(myWidget1);
    // layout->addWidget(myWidget2);

    // Set layout in QWidget
    QWidget *window = new QWidget();
    window->setLayout(layout);


    // Set QWidget as the central layout of the main window
    mainWindow.setCentralWidget(window);




    // QLabel* label = new QLabel();
    // label->setText(QString::fromStdString(tutorial + kernel_info));
    // label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    // label->setWordWrap(true);


    // std::cout << "not getting any stdout?" << std::endl;
    // mainWindow.setCentralWidget(label);


    // QPushButton btn("BTN");
    // QObject::connect(&btn, &QPushButton::clicked, [&](){
    //     // create_json_file(kernel_info);
    //     std::cout<<"clicked button\n";
    // });
    
    mainWindow.show();
    std::cout << "between show and exec" << std::endl;
    application.exec();
    return 0;
}
