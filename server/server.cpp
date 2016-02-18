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
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <istream>
#include <iostream>

using namespace std;


bool Server::checkUser(unsigned user)
{
    for (const auto &usr: this->users)
        if (usr == user)
            return true;

    return false;
}

Server::Server(const shared_ptr<ILog> &log, const shared_ptr<IDatabase> &db, const shared_ptr<IConfigs> &cfg)
{
    this->m_log = log;
    this->m_db = db;
    this->m_cfg = cfg;
}

void Server::newSession(shared_ptr<ITcpClient> client)
{
    Data rdata;
    char data[DATA_SIZE];   
    auto dbc = m_cfg->getDatabaseCfg();

    memset(data, 0x00, DATA_SIZE);
    try {
        client->recv(data, DATA_SIZE);
    }
    catch (const string &err) {
        m_log->local("[NEW_CLIENT]: " + err, LOG_INFORMATION);
        return;
    }
    try {
        string out(data);
        boost::property_tree::ptree pt;
        istringstream is(out);

        boost::property_tree::read_json(is, pt);
        rdata.id = pt.get<unsigned>("Id");
        rdata.temp = pt.get<float>("Temp");
        rdata.hum = pt.get<float>("Hum");
    }
    catch (...) {
        m_log->local("[NEW_CLIENT]: Error parsing json data.", LOG_INFORMATION);
        return;
    }
    if (!checkUser(rdata.id)) {
        m_log->local("[NEW_CLIENT]: Bad ID!", LOG_ERROR);
        return;
    }
    cout << "[NEW_CLIENT] id: " << rdata.id << " Temp: " << rdata.temp << " Hum: " << rdata.hum << "%." << endl;

    try {
        m_db->connect(dbc->ip, dbc->user, dbc->passwd, dbc->base);
        m_db->addToBase(rdata.id, rdata.temp, rdata.hum);
        m_db->close();
    }
    catch (const string &err) {
        m_log->local("[DATABASE]: " + err, LOG_ERROR);
        return;
    }
}

void Server::acceptError(void) const
{
    m_log->local("[SERVER]: Fail accepting client.", LOG_INFORMATION);
}

void Server::start(unsigned port)
{
    TcpServer::start(port);
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
