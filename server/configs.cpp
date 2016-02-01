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

#include "configs.h"
#include <fstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


void Configs::load(const string &filename)
{
    std::ifstream ifs;
    boost::property_tree::ptree pt;

    ifs.open(filename);
    if (!ifs.is_open())
        throw string("File not found.");

    try {
        boost::property_tree::read_json(ifs, pt);
    }
    catch (...) {
        ifs.close();
        throw string("Fail parsing json file.");
    }

    try {
        msc.port = pt.get<unsigned>("MeteoServer.Port");
        rlc.ip = pt.get<string>("RemoteLog.Ip");
        rlc.port = pt.get<unsigned>("RemoteLog.Port");
        dbc.id = pt.get<unsigned>("Database.Id");
        dbc.ip = pt.get<string>("Database.Ip");
        dbc.user = pt.get<string>("Database.User");
        dbc.passwd = pt.get<string>("Database.Passwd");
        dbc.base = pt.get<string>("Database.Base");
    }
    catch (...) {
        ifs.close();
        throw string("Fail reading configs values.");
    }
    ifs.close();
}

void Configs::print()
{
    cout << "Configs:" << endl << "------------------------" << endl;
    cout << "MeteoServerPort: " << msc.port << endl;
    cout << "RemoteLogIp: " << rlc.ip << endl;
    cout << "RemoteLogPort: " << rlc.port << endl;
    cout << "DatabaseId: " << dbc.id << endl;
    cout << "DatabaseIp: " << dbc.ip << endl;
    cout << "DatabaseUser: " << dbc.user << endl;
    cout << "DatabasePasswd: " << dbc.passwd << endl;
    cout << "DatabaseBase: " << dbc.base << endl;
}
