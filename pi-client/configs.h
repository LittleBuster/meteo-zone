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

using namespace std;

typedef struct {
    unsigned id;
    string ip;
    unsigned port;
    unsigned interval;
} MeteoServerCfg;

typedef struct {
    string ip;
    unsigned port;
} RemoteLogCfg;

typedef struct {
    unsigned out;
    unsigned in;
} SensorsCfg;

typedef struct {
    unsigned port;
    unsigned i2c;
} LcdCfg;


class IConfigs
{
public:
    virtual const MeteoServerCfg* getMeteoCfg(void) const = 0;
    virtual const RemoteLogCfg* getRLogCfg(void) const = 0;
    virtual const SensorsCfg* getSensorsCfg(void) const = 0;
    virtual const LcdCfg* getLcdCfg(void) const = 0;
    virtual void load(const string &filename) = 0;
    virtual void print(void) const = 0;
};


class Configs: public IConfigs
{
private:
    MeteoServerCfg msc;
    RemoteLogCfg rlc;
    SensorsCfg sc;
    LcdCfg lc;

public:
    inline const MeteoServerCfg* getMeteoCfg(void) const {
        return &msc;
    }

    inline const RemoteLogCfg* getRLogCfg(void) const {
        return &rlc;
    }

    inline const SensorsCfg* getSensorsCfg(void) const {
        return &sc;
    }

    inline const LcdCfg* getLcdCfg(void) const {
        return &lc;
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
