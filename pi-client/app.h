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

#ifndef __APP_H__
#define __APP_H__

#include "sender.h"
#include "configs.h"
#include <logger/log.h>

class App
{
private:
    shared_ptr<ISender> _sender;
    shared_ptr<IConfigs> _cfg;
    shared_ptr<logger::ILog> _log;

public:
    explicit App(const shared_ptr<ISender> &sender, const shared_ptr<IConfigs> &cfg, const shared_ptr<logger::ILog> &log);

    int start(void);
};


#endif
