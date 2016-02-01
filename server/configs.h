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
    virtual MeteoServerCfg* getMeteoCfg(void) = 0;
    virtual RemoteLogCfg* getRLogCfg(void) = 0;
    virtual DatabaseCfg* getDatabaseCfg(void) = 0;
    virtual void load(const string &filename) = 0;
    virtual void print(void) = 0;
};


class Configs: public IConfigs
{
private:
    MeteoServerCfg msc;
    RemoteLogCfg rlc;
    DatabaseCfg dbc;

public:
    inline MeteoServerCfg* getMeteoCfg(void) {
        return &msc;
    }

    inline RemoteLogCfg* getRLogCfg(void) {
        return &rlc;
    }

    inline DatabaseCfg* getDatabaseCfg(void) {
        return &dbc;
    }

    /*
     * Loading configs from json file
     */
    void load(const string &filename);

    /*
     * Print loading configs for debugging
     */
    void print(void);
};


#endif
