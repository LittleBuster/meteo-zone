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

#ifndef __TCPSOCKET_H__
#define __TCPSOCKET_H__

#include <memory>
#include <thread>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;


class ITcpClient
{
public:
    virtual void connect(const string &ip, unsigned port) = 0;
    virtual void send(const void *data, size_t len) = 0;
    virtual void recv(void *data, size_t len) const = 0;
    virtual void close(void) const = 0;
};


class TcpClient: public ITcpClient
{
private:
    boost::asio::io_service io_service;
    shared_ptr<tcp::socket> s_client;

public:
    explicit TcpClient();

    explicit TcpClient(const shared_ptr<tcp::socket> &parent_sock);

    /**
     * Connect to remote socket
     * @ip: remote ip address
     * @port: remote socket port
     *
     * throw: error if fail connecting
     */
    void connect(const string &ip, unsigned port);

    /**
     * Send data to server
     * @data: sending data
     * @len: data length
     *
     * throw: error if fail sending data
     */
    void send(const void *data, size_t len);

    /**
     * Receive data from server
     * @data: receiving data
     * @len: data length
     *
     * throw: error if fail receiving data
     */
    void recv(void *data, size_t len) const;

    /*
     * Close connection
     */
    void close(void) const;
};


#endif
