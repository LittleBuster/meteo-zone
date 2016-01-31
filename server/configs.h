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


class IConfigs
{
public:
};


class Configs: public IConfigs
{
private:
    shared_ptr<ILog> m_log;

public:
    Configs(shared_ptr<ILog> log);
};


#endif
