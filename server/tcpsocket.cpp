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

#include "tcpsocket.h"


TcpSocket::TcpSocket()
{
    this->s_client = make_shared<tcp::socket>(io_service);
}

TcpSocket::TcpSocket(shared_ptr<tcp::socket> parent_sock)
{
    this->s_client = parent_sock;
}

void TcpSocket::send(const void *data, size_t len) const
{
    boost::system::error_code error;

    this->s_client->write_some(boost::asio::buffer(data, len), error);
    if (error)
        throw string("Fail sending data.");
}

void TcpSocket::recv(void *data, size_t len)
{
    size_t r_len;
    boost::system::error_code error;

    r_len = s_client->read_some(boost::asio::buffer(data, len), error);
    if (error == boost::asio::error::eof)
        return;
    else if (error)
        throw string("Fail receiving data.");

    if (r_len != len)
        throw string("Fail receiving data. Bad data length.");
}

void TcpSocket::start(unsigned port) const
{
    tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
    for (;;) {
        auto sock = make_shared<tcp::socket>(io_service);
        try {
            a.accept(*sock);
        }
        catch (...) {
            this->acceptError();
            continue;
        }
        auto client = make_shared<TcpSocket>(sock);
        thread(boost::bind(&TcpSocket::newSession, this, client)).detach();
    }
}
