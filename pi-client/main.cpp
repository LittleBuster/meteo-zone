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

#include <memory>
#include "app.h"
#include "configs.h"
#include "log.h"
#include "sender.h"
#include "tcpclient.h"
#include "lcd.h"
#include <dht22.h>


int main(void)
{
    auto dht_out = make_shared<DHT22>();
    auto dht_in = make_shared<DHT22>();
    auto cfg = make_shared<Configs>();
    auto client = make_shared<TcpClient>();
    auto lcd = make_shared<LCD>();
    auto log = make_shared<Log>(client);
    auto sender = make_shared<Sender>(client, dht_out, dht_in, cfg, lcd, log);

    auto app = make_shared<App>(sender, cfg, log);
    return app->start();
}
