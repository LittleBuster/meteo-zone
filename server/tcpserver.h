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

#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__


class ITcpServer
{
public:
    virtual void start(unsigned port) = 0;
};


class TcpServer: public ITcpServer
{
public:
    TcpServer();

    void start(unsigned port);
};


#endif
