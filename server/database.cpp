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

#include "database.h"
#include <iostream>
#include <boost/lexical_cast.hpp>


void Database::connect(const string &ip, const string &user, const string &passwd, const string &base)
{
    string connStr = "dbname=" + base + " user=" + user + " password=" + passwd + " hostaddr=" + ip + " port=5432";
    _conn = PQconnectdb(connStr.c_str());
    if (PQstatus(_conn) == CONNECTION_BAD)
        throw string("Can not connect to database.");
}

void Database::addToBase(unsigned id, float temp, float hum)
{
    string req;
    char dt[16];

    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);

    req = "INSERT INTO meteo";
    req += boost::lexical_cast<string>(id);
    req += "(temp, hum, date) VALUES ('";
    req += boost::lexical_cast<string>(temp) + "', '";
    req += boost::lexical_cast<string>(hum) + "', '";

    strftime(dt, 15, "%F", timeinfo);
    req += string(dt) + " ";
    strftime(dt, 15, "%T", timeinfo);
    req += string(dt) + "')";

    PGresult *res = PQexec(_conn, req.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
        throw string("Fail insert record to database.");
}
