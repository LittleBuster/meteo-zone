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


App::App(shared_ptr<ILog> log, shared_ptr<IDatabase> db, shared_ptr<IConfigs> cfg, shared_ptr<ITcpSocket> server)
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
