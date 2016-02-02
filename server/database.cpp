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
    mysql_init(&mysql);
    conn = mysql_real_connect(&mysql, ip.c_str(), user.c_str(), passwd.c_str(), base.c_str(), 3306, NULL, 0);
    if (conn == NULL)
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

    cout << req << endl;
    int qs = mysql_query(conn, req.c_str());
    if (qs != 0)
        throw string("Fail insert record to database.");
}

void Database::close()
{
    mysql_close(conn);
    mysql_close(&mysql);
}
