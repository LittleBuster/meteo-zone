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

#include "log.h"


Log::Log(shared_ptr<ITcpSocket> client)
{
    this->m_client = client;
}

void Log::connectToLog()
{

}

void Log::closeLog()
{

}

void Log::local(const string &message, LogType err_type)
{

}

void Log::remote(const string &message, LogType err_type)
{

}
