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
#include <boost/lexical_cast.hpp>


App::App(const shared_ptr<ISender> &sender, const shared_ptr<IConfigs> &cfg, const shared_ptr<logger::ILog> &log)
{
    _sender = sender;
    _cfg = cfg;
    _log = log;
}

int App::start(void)
{
    cout << "Starting meteo client..." << endl;
    _log->setLogFile("/var/log/meteo.log");

    try {
        _cfg->load("/etc/meteo.cfg");
    }
    catch (const string &err) {
        _log->local("[CONFIGS]: " + err, logger::LOG_ERROR);
        return -1;
    }

    auto msc = _cfg->getMeteoCfg();
    auto rlc = _cfg->getRLogCfg();
    _log->setRemoteLogCfg(rlc->ip, rlc->port, boost::lexical_cast<string>(msc->id));

    _sender->setInterval(msc->interval);
    try {
        _sender->start();
    }
    catch (const string &err) {
        _log->local("[OUTSIDE_SENSOR]: " + err, logger::LOG_ERROR);
        return -1;
    }

    for (;;) {
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
}
