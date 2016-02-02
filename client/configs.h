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
    unsigned id;
    string ip;
    unsigned port;
} MeteoServerCfg;


class IConfigs
{
public:
    virtual MeteoServerCfg* getMeteoCfg(void) = 0;
    virtual void load(const string &filename) = 0;
    virtual void print(void) = 0;
};


class Configs: public IConfigs
{
private:
    MeteoServerCfg msc;

public:
    inline MeteoServerCfg* getMeteoCfg(void) {
        return &msc;
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
