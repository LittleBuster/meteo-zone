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

#include "tcpserver.h"


void TcpServer::start(unsigned port)
{
    try {
        acpt = make_shared<tcp::acceptor>(io_service, tcp::endpoint(tcp::v4(), port));
    }
    catch (...) {
        throw string("Binding ip address and port fail.");
    }
    for (;;) {
        auto sock = make_shared<tcp::socket>(io_service);
        try {
            acpt->accept(*sock);
        }
        catch (...) {
            this->acceptError();
            continue;
        }
        auto client = make_shared<TcpClient>(sock);
        thread(boost::bind(&TcpServer::newSession, this, client)).detach();
    }
}
