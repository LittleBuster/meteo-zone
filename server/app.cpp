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
#include <boost/lexical_cast.hpp>


App::App(const shared_ptr<logger::ILog> &log, const shared_ptr<IConfigs> &cfg, const shared_ptr<IServer> &server)
{
    this->_log = log;
    this->_cfg = cfg;
    this->_server = server;
}

int App::start(void)
{
    cout << "Starting weather server..." << endl;
    _log->setLogFile("/var/log/meteosrv.log");
    cout << "Log file setup." << endl;

    try {
        _cfg->load("/etc/meteosrv.cfg");
    }
    catch (const string &err) {
        _log->local("[CONFIGS]: " + err, logger::LOG_ERROR);
        return -1;
    }

    auto rlc = _cfg->getRLogCfg();
    auto msc = _cfg->getMeteoCfg();
    auto dbc = _cfg->getDatabaseCfg();
    _log->setRemoteLogCfg(rlc->ip, rlc->port, boost::lexical_cast<string>(dbc->id));
    cout << "Server configs loaded." << endl;

    try {
        _server->loadUsers("/etc/meteo-users.cfg");
        cout << "Users list loaded." << endl;
        _server->start(msc->port);
    }
    catch (const string &err) {
        _log->local("[SERVER]: " + err, logger::LOG_ERROR);
        return -1;
    }
    return 0;
}
