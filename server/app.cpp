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

#include "app.h"
#include <iostream>


App::App(shared_ptr<ILog> log, shared_ptr<IConfigs> cfg, shared_ptr<IServer> server)
{
    this->m_log = log;
    this->m_cfg = cfg;
    this->m_server = server;
}

int App::start()
{
    cout << "Starting weather server..." << endl;
    m_log->setLogFile("/var/log/meteosrv.log");

    try {
        m_cfg->load("/etc/meteosrv.cfg");
    }
    catch (const string &err) {
        m_log->local("[CONFIGS]: " + err, LOG_ERROR);
        return -1;
    }
    auto rlc = m_cfg->getRLogCfg();
    auto msc = m_cfg->getMeteoCfg();
    m_log->setRemoteLogCfg(rlc->ip, rlc->port);

    try {
        m_server->loadUsers("/etc/meteo-users.cfg");
        m_server->start(msc->port);
    }
    catch (const string &err) {
        m_log->local("[SERVER]: " + err, LOG_ERROR);
        return -1;
    }
    return 0;
}
