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

#ifndef __SERVER_H__
#define __SERVER_H__

#include "net/tcpserver.h"
#include "database.h"
#include "configs.h"
#include "net/tcpclient.h"
#include <logger/log.h>
#include <vector>

#define DATA_SIZE 255

typedef struct {
    unsigned id;
    float temp;
    float hum;
} Data;


class IServer: public ITcpServer
{
public:
    virtual void loadUsers(const string &filename) = 0;
};


class Server final: public IServer, public TcpServer
{
private:
    shared_ptr<logger::ILog> _log;
    shared_ptr<IDatabase> _db;
    shared_ptr<IConfigs> _cfg;
    vector<unsigned> _users;

    using IServer::start;

    /**
     * Check new user in local base
     * @user: new user id
     *
     * returns: false if user not exists
     * returns: true if user was found
     */
    bool checkUser(unsigned user) const;

public:
    explicit Server(const shared_ptr<logger::ILog> &log, const shared_ptr<IDatabase> &db, const shared_ptr<IConfigs> &cfg);

    /*
     * New client connection session
     */
    virtual void newSession(shared_ptr<ITcpClient> client) override final;

    /*
     * Accepting new client error signal
     */
    virtual void acceptError(void) const override final;

    /**
     * Start local servrt
     * @port: binding local port
     *
     * throw: error if fail binding local ip and port
     */
    virtual void start(unsigned port) override final;

    /**
     * Loading user list
     * @filename: text file with users ids list
     *
     * throw: error if file not found
     * throw: error if users list incorrect
     */
    void loadUsers(const string &filename);
};


#endif
