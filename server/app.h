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

#ifndef __APP_H__
#define __APP_H__

#include "log.h"
#include "database.h"
#include "configs.h"
#include "server.h"
#include "tcpserver.h"


class App
{
private:
    shared_ptr<ILog> m_log;
    shared_ptr<IDatabase> m_db;
    shared_ptr<IConfigs> m_cfg;
    shared_ptr<ITcpServer> m_server;

public:
    App(shared_ptr<ILog> log, shared_ptr<IDatabase> db, shared_ptr<IConfigs> cfg, shared_ptr<ITcpServer> server);

    void start(void);
};


#endif
