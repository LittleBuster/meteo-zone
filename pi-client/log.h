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

#ifndef __LOG_H__
#define __LOG_H__

#include <string>
#include <memory>
#include <tcpsocket.h>

using namespace std;


typedef enum {
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFORMATION
} LogType;


typedef struct {
    string ip;
    unsigned port;
} RemoteLog;


class ILog
{
public:
    virtual void setRemoteLogCfg(const string &ip, unsigned port) = 0;
    virtual void setLogFile(const string &filepath) = 0;
    virtual void local(const string &message, LogType log_type) = 0;
    virtual void remote(const string &message, LogType log_type) = 0;
};


class Log: public ILog
{
private:
    shared_ptr<ITcpSocket> m_client;
    RemoteLog remote_log;
    string log_path;

    string makeLogMsg(const string &msg, LogType type);

public:
    Log(shared_ptr<ITcpSocket> client);

    /**
     * Set remote log server configs
     * @ip: remote log server ip address
     * @port: remote log server port
     */
    inline void setRemoteLogCfg(const string &ip, unsigned port) {
        remote_log.ip = ip;
        remote_log.port = port;
    }

    /*
     * Set path for saving log data in local file
     */
    inline void setLogFile(const string &filepath) {
        this->log_path = filepath;
    }

    /**
     * Saving log data in local file
     * @message: log message
     * @log_type: message type
     */
    void local(const string &message, LogType log_type);

    /**
     * Saving log data to remote server
     * @message: log message
     * @log_type: message type
     */
    void remote(const string &message, LogType log_type);
};


#endif
