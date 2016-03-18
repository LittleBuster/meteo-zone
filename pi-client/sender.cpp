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


Sender::Sender(const shared_ptr<ITcpClient> &client, const shared_ptr<IDHT22> &dht_out, const shared_ptr<IDHT22> &dht_in,
               const shared_ptr<IConfigs> &cfg, const shared_ptr<ILCD> &lcd, const shared_ptr<logger::ILog> &log)
{
    _client = client;
    _dhtIn = dht_in;
    _dhtOut = dht_out;
    _cfg = cfg;
    _lcd = lcd;
    _log = log;
    _isInside = false;
    _interval = 0;
}

void Sender::start(void)
{
    auto sc = _cfg->getSensorsCfg();
    auto lc = _cfg->getLcdCfg();

    _dhtOut->init(sc->out);
    try {
        _dhtIn->init(sc->in);
        _isInside = true;
    }
    catch (const string &err) {
        _log->local("[INSIDE_SENSOR]: " + err, logger::LOG_WARNING);
        _isInside = false;
    }
    if (sc->in == 0)
        _isInside = false;

    _lcd->init(lc->port, lc->i2c);

    _timer = make_shared<deadline_timer>(io, boost::posix_time::seconds(_interval));
    _timer->async_wait(boost::bind(&Sender::send, this));
    io.run();
}

#include <boost/thread.hpp>

void Sender::send(void)
{
    bool isRead = false;
    float out_temp = 0.0f;
    float out_hum = 0.0f;
    float in_temp = 0.0f;
    float in_hum = 0.0f;
    auto msc = _cfg->getMeteoCfg();

    for (unsigned i = 0; i < 5; i++) {
        try {
            _dhtOut->readData(out_temp, out_hum);
            isRead = true;
        }
        catch (...) {
            cout << "Retry reading outside sensor..." << endl;
            boost::this_thread::sleep(boost::posix_time::seconds(1));
        }
    }

    if (!isRead) {
        _log->local("[OUTSIDE_SENSOR]: Can not read data.", logger::LOG_ERROR);
        _timer->expires_at(_timer->expires_at() + boost::posix_time::seconds(_interval));
        _timer->async_wait(boost::bind(&Sender::send, this));
        return;
    }

    if (_isInside) {
        try {
            _dhtIn->readData(in_temp, in_hum);
        }
        catch (const string &err) {
            _log->local("[INSIDE_SENSOR]: " + err, logger::LOG_WARNING);
            in_temp = 0.0f;
            in_hum = 0.0f;
        }
    }
    cout << "[OUT_TEMP]: " << out_temp << " [OUT_HUM]: " << out_hum << " [IN_TEMP]: " << in_temp << " [IN_HUM]: " << in_hum << endl;
    _lcd->clear();
    _lcd->showData(out_temp, out_hum, in_temp, in_hum);

    try {
        string out;
        out = "{\"Id\": " + boost::lexical_cast<string>(msc->id) + ", \"Temp\": ";
        out += boost::lexical_cast<string>(out_temp) + ", \"Hum\": " + boost::lexical_cast<string>(out_hum) + "}";

        _client->connect(msc->ip, msc->port);
        _client->send((void *)out.c_str(), DATA_SIZE);
        _client->close();
    }
    catch (const string &err) {
        _log->local("[CLIENT]: " + err, logger::LOG_ERROR);
    }

    _timer->expires_at(_timer->expires_at() + boost::posix_time::seconds(_interval));
    _timer->async_wait(boost::bind(&Sender::send, this));
}
