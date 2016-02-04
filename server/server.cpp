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
#include <fstream>
#include <omp.h>
#include <boost/lexical_cast.hpp>


bool Server::checkUser(unsigned user)
{
    #pragma omp parallel for
    for (const auto &usr: this->users)
        if (usr == user)
            return true;

    return false;
}

Server::Server(shared_ptr<ILog> log, shared_ptr<IDatabase> db, shared_ptr<IConfigs> cfg): TcpSocket()
{
    this->m_log = log;
    this->m_db = db;
    this->m_cfg = cfg;
}

void Server::newSession(shared_ptr<ITcpSocket> client)
{
    auto dbc = m_cfg->getDatabaseCfg();

    //TODO: Add reading client data

    try {
        m_db->connect(dbc->ip, dbc->user, dbc->passwd, dbc->base);
        m_db->addToBase(12345678, 44.37, 90.33);
        m_db->close();
    }
    catch (const string &err) {
        m_log->local("[DATABASE]: " + err, LOG_ERROR);
        return;
    }
}

void Server::acceptError(void)
{
    m_log->local("[SERVER]: Fail accepting client.", LOG_INFORMATION);
}

void Server::loadUsers(const string &filename)
{
    string usr;
    ifstream file;
    file.open(filename);
    if (!file.is_open())
        throw string("Fail open users list file.");

    try {
        while (getline(file, usr))
            users.push_back(boost::lexical_cast<unsigned>(usr));
    }
    catch (...) {
        file.close();
        throw string("Fail reading user.");
    }
    file.close();
}
