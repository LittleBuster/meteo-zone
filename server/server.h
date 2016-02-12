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

#include "log.h"
#include "database.h"
#include "configs.h"
#include "tcpsocket.h"
#include <vector>

#define DATA_SIZE 255

typedef struct {
    unsigned id;
    float temp;
    float hum;
} Data;


class IServer: public virtual ITcpSocket
{
public:
    virtual void loadUsers(const string &filename) = 0;
};


class Server final: public IServer, public TcpSocket
{
private:
    shared_ptr<ILog> m_log;
    shared_ptr<IDatabase> m_db;
    shared_ptr<IConfigs> m_cfg;
    vector<unsigned> users;

    bool checkUser(unsigned user);

public:
    Server(const shared_ptr<ILog> &log, const shared_ptr<IDatabase> &db, const shared_ptr<IConfigs> &cfg);

    /*
     * New client connection session
     */
    virtual void newSession(shared_ptr<ITcpSocket> client) override final;

    /*
     * Accepting new client error signal
     */
    virtual void acceptError(void) override final;

    /*
     * Loading user list
     */
    void loadUsers(const string &filename);
};


#endif
