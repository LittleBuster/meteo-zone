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

#include "sender.h"


Sender::Sender(shared_ptr<ITcpSocket> client, shared_ptr<IDHT22> dht_out, shared_ptr<IDHT22> dht_in,
               shared_ptr<IConfigs> cfg, shared_ptr<ILog> log)
{
    this->m_client = client;
    this->m_dht_in = dht_in;
    this->m_dht_out = dht_out;
    this->m_cfg = cfg;
    this->m_log = log;
    this->is_inside = false;
}

void Sender::start(void)
{
    auto sc = m_cfg->getSensorsCfg();

    m_dht_out->init(sc->out);
    try {
        m_dht_in->init(sc->in);
        this->is_inside = true;
    }
    catch (const string &err) {
        m_log->local("[INSIDE_SENSOR]: " + err, LOG_WARNING);
        this->is_inside = false;
    }

    this->timer = make_shared<deadline_timer>(io, boost::posix_time::seconds(this->interval));
    this->timer->async_wait(boost::bind(&Sender::send, this));
    io.run();
}

void Sender::send(void)
{
    float out_temp, out_hum, in_temp, in_hum;
    auto msc = m_cfg->getMeteoCfg();

    try {
        m_dht_out->readData(out_temp, out_hum);
    }
    catch(const string &err) {
        m_log->local("[OUTSIDE_SENSOR]: " + err, LOG_ERROR);
        timer->expires_at(timer->expires_at() + boost::posix_time::seconds(this->interval));
        timer->async_wait(boost::bind(&Sender::send, this));
        return;
    }

    if (this->is_inside) {
        try {
            m_dht_in->readData(in_temp, in_hum);
        }
        catch (const string &err) {
            m_log->local("[INSIDE_SENSOR]: " + err, LOG_WARNING);
            in_temp = 0.0f;
            in_hum = 0.0f;
        }
    }
    cout << "[OUT_TEMP]: " << out_temp << " [OUT_HUM]: " << out_hum << " [IN_TEMP]: " << in_temp << " [IN_HUM]: " << in_hum << endl;

    try {
        string out;
        out = "{\"Id\": " + boost::lexical_cast<string>(msc->id) + ", \"Temp\": ";
        out += boost::lexical_cast<string>(out_temp) + ", \"Hum\": " + boost::lexical_cast<string>(out_hum) + "}";

        this->m_client->connect(msc->ip, msc->port);
        this->m_client->send((void *)out.c_str(), DATA_SIZE);
        this->m_client->close();
    }
    catch (const string &err) {
        m_log->local("[CLIENT]: " + err, LOG_ERROR);
    }

    timer->expires_at(timer->expires_at() + boost::posix_time::seconds(this->interval));
    this->timer->async_wait(boost::bind(&Sender::send, this));
}
