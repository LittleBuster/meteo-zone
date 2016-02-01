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

#include "log.h"
#include "database.h"
#include "configs.h"
#include "server.h"
#include "app.h"


int main()
{
    auto db = make_shared<Database>();
    auto cfg = make_shared<Configs>();
    auto client = make_shared<TcpSocket>();
    auto log = make_shared<Log>(client);
    auto server = make_shared<Server>(log, db, cfg);

    auto app = make_shared<App>(log, cfg, server);
    return app->start();
}
