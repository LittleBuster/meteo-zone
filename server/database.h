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

#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>
#include <mysql/mysql.h>

using namespace std;


class IDatabase
{
public:
    virtual void connect(const string &ip, const string &user, const string &passwd, const string &base) = 0;
    virtual void addToBase(unsigned id, float temp, float hum) = 0;
    virtual void close(void) = 0;
};


class Database: public IDatabase
{
private:
    MYSQL mysql;
    MYSQL *conn;

public:
    /**
     * Connection to database
     * @ip: remote ip address
     * @user: database username
     * @passwd: database user password
     * @base: database name
     *
     * throw: error if connection fail
     */
    void connect(const string &ip, const string &user, const string &passwd, const string &base);

    /**
     * Add record to database
     * @id: meteo user
     * @temp: temperature value
     * @hum: humidity value
     *
     * throw: error if fail record addition to database
     */
    void addToBase(unsigned id, float temp, float hum);

    /*
     * Disconnection from database
     */
    void close(void);
};


#endif
