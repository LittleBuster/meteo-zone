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


class ITcpSocket
{
public:
    virtual void newSession(shared_ptr<ITcpSocket> client) = 0;
    virtual void acceptError(void) = 0;
    virtual void connect(const string &ip, unsigned port) = 0;
    virtual void send(const void *data, size_t len) const = 0;
    virtual void recv(void *data, size_t len) = 0;
    virtual void start(unsigned port) = 0;
    virtual void close(void) = 0;
};


class TcpSocket: public ITcpSocket
{
private:
    boost::asio::io_service io_service;
    shared_ptr<tcp::socket> s_client;

public:
    TcpSocket();

    TcpSocket(shared_ptr<tcp::socket> parent_sock);

    /*
     * New client connection session
     */
    virtual void newSession(shared_ptr<ITcpSocket> client) { };

    /*
     * Accepting new client error signal
     */
    virtual void acceptError(void) { };

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
    void send(const void *data, size_t len) const;

    /**
     * Receive data from server
     * @data: receiving data
     * @len: data length
     *
     * throw: error if fail receiving data
     */
    void recv(void *data, size_t len);

    /**
     * Binding tcp server
     * @port: local tcp port
     *
     * throw: error if fail binding
     */
    void start(unsigned port);

    /*
     * Close connection
     */
    void close(void);
};


#endif
