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

#ifndef __CONFIGS_H__
#define __CONFIGS_H__

#include <memory>
#include "log.h"

using namespace std;

typedef struct {
    unsigned port;
} MeteoServerCfg;

typedef struct {
    string ip;
    unsigned port;
} RemoteLogCfg;

typedef struct {
    unsigned id;
    string ip;
    string user;
    string passwd;
    string base;
} DatabaseCfg;


class IConfigs
{
public:
    virtual const MeteoServerCfg* getMeteoCfg(void) const = 0;
    virtual const RemoteLogCfg* getRLogCfg(void) const = 0;
    virtual const DatabaseCfg* getDatabaseCfg(void) const = 0;
    virtual void load(const string &filename) = 0;
    virtual void print(void) const = 0;
};


class Configs: public IConfigs
{
private:
    MeteoServerCfg msc;
    RemoteLogCfg rlc;
    DatabaseCfg dbc;

public:
    inline const MeteoServerCfg* getMeteoCfg(void) const {
        return &msc;
    }

    inline const RemoteLogCfg* getRLogCfg(void) const {
        return &rlc;
    }

    inline const DatabaseCfg* getDatabaseCfg(void) const {
        return &dbc;
    }

    /*
     * Loading configs from json file
     */
    void load(const string &filename);

    /*
     * Print loading configs for debugging
     */
    void print(void) const;
};


#endif
