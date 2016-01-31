#include "server.h"
#include "tcpserver.h"

Server::Server(shared_ptr<ILog> log, shared_ptr<IDatabase> db, shared_ptr<IConfigs> cfg): TcpServer()
{
    this->m_log = log;
    this->m_db = db;
    this->m_cfg = cfg;
}
