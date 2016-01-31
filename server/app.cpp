#include "app.h"
#include <iostream>


App::App(shared_ptr<ILog> log, shared_ptr<IDatabase> db, shared_ptr<IConfigs> cfg, shared_ptr<ITcpServer> server)
{
    this->m_log = log;
    this->m_db = db;
    this->m_cfg = cfg;
    this->m_server = server;
}

void App::start()
{
    cout << "Starting weather server..." << endl;
    m_server->start(5000);
}
