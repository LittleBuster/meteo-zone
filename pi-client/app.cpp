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
#include <boost/thread.hpp>


App::App(shared_ptr<ISender> sender, shared_ptr<IConfigs> cfg, shared_ptr<ILog> log)
{
    m_sender = sender;
    m_cfg = cfg;
    m_log = log;
}

int App::start(void)
{
    cout << "Starting weather server..." << endl;
    m_log->setLogFile("/var/log/meteo.log");

    try {
        m_cfg->load("/etc/meteo.cfg");
    }
    catch (const string &err) {
        m_log->local("[CONFIGS]: " + err, LOG_ERROR);
        return -1;
    }

    auto msc = m_cfg->getMeteoCfg();
    auto rlc = m_cfg->getRLogCfg();
    m_log->setRemoteLogCfg(rlc->ip, rlc->port);

    m_sender->setInterval(msc->interval);
    try {
        m_sender->start();
    }
    catch (const string &err) {
        m_log->local("[OUTSIDE_SENSOR]: " + err, LOG_ERROR);
        return -1;
    }

    for (;;) {
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
}
