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

#include "tcpsocket.h"
#include "configs.h"
#include "log.h"
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
    shared_ptr<ITcpSocket> m_client;
    shared_ptr<IDHT22> m_dht_out;
    shared_ptr<IDHT22> m_dht_in;
    shared_ptr<IConfigs> m_cfg;
    shared_ptr<ILCD> m_lcd;
    shared_ptr<ILog> m_log;
    io_service io;
    shared_ptr<deadline_timer> timer;
    unsigned interval;
    bool is_inside;

    void send(void);

public:
    Sender(const shared_ptr<ITcpSocket> &client, const shared_ptr<IDHT22> &dht_out, const shared_ptr<IDHT22> &dht_in,
           const shared_ptr<IConfigs> &cfg, const shared_ptr<ILCD> &lcd, const shared_ptr<ILog> &log);

    inline void setInterval(unsigned seconds) {
        this->interval = seconds;
    }

    void start(void);
};


#endif
