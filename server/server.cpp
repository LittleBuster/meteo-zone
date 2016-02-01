/* Meteo-zone server
 *
 * Copyright (C) 2016 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#include "server.h"


Server::Server(shared_ptr<ILog> log, shared_ptr<IDatabase> db, shared_ptr<IConfigs> cfg): TcpSocket()
{
    this->m_log = log;
    this->m_db = db;
    this->m_cfg = cfg;
}

void Server::newSession(shared_ptr<ITcpSocket> client)
{

}

void Server::acceptError(void)
{

}
