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

#ifndef __SENDER_H__
#define __SENDER_H__

#include "tcpclient.h"
#include "configs.h"
#include <logger/log.h>
#include "lcd.h"
#include <dht22.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::asio;

#define DATA_SIZE 255


class ISender
{
public:
    virtual void setInterval(unsigned seconds) = 0;
    virtual void start(void) = 0;
};


class Sender: public ISender
{
private:
    shared_ptr<ITcpClient> _client;
    shared_ptr<IDHT22> _dhtOut;
    shared_ptr<IDHT22> _dhtIn;
    shared_ptr<IConfigs> _cfg;
    shared_ptr<ILCD> _lcd;
    shared_ptr<logger::ILog> _log;
    io_service io;
    shared_ptr<deadline_timer> _timer;
    unsigned _interval;
    bool _isInside;

    void send(void);

public:
    explicit Sender(const shared_ptr<ITcpClient> &client, const shared_ptr<IDHT22> &dht_out, const shared_ptr<IDHT22> &dht_in,
           const shared_ptr<IConfigs> &cfg, const shared_ptr<ILCD> &lcd, const shared_ptr<logger::ILog> &log);

    inline void setInterval(unsigned seconds) {
        _interval = seconds;
    }

    void start(void);
};


#endif
