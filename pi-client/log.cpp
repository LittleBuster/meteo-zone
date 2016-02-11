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

#include "log.h"
#include <iostream>
#include "fstream"


string Log::makeLogMsg(const string &msg, LogType type)
{
    string out;
    char dt[16];

    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);

    strftime(dt, 15, "%F", timeinfo);
    out = "[" + string(dt) + "][";
    strftime(dt, 15, "%T", timeinfo);
    out += string(dt) + "][";

    switch (type) {
        case LOG_ERROR: {
            out += "ERROR]";
            break;
        }
        case LOG_WARNING: {
            out += "WARNING]";
            break;
        }
        case LOG_INFORMATION: {
            out += "INFO]";
            break;
        }
    }
    out += msg;
    return out;
}

Log::Log(shared_ptr<ITcpSocket> client)
{
    this->m_client = client;
    this->setLogFile("");
    this->remote_log.ip = "";
    this->remote_log.port = 0;
}

void Log::local(const string &message, LogType err_type)
{
    string msg = makeLogMsg(message, err_type);
    cout << msg << endl;

    if (this->log_path == "")
        return;

    try {
        ofstream log;
        log.open(this->log_path, ios::out|ios::ate|ios::app);
        log << msg << "\n";
        log.close();
    }
    catch (...) {
        cout << "Fail writing to log file." << endl;
    }
}

void Log::remote(const string &message, LogType err_type)
{
    string msg = makeLogMsg(message, err_type);
    cout << msg << endl;

    try {
        m_client->connect(remote_log.ip, remote_log.port);
        m_client->send(msg.c_str(), 255);
        m_client->close();
    }
    catch (const string &err) {
        local("[REMOTE_LOG]: " + err, LOG_WARNING);
        return;
    }
}
