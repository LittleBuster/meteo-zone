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

#include "lcd.h"
#include <pcf8574.h>
#include <wiringPi.h>
#include "/usr/include/lcd.h"
#include <string>

using namespace std;


void LCD::init(unsigned port_num, unsigned i2c_addr)
{
    pcf8574Setup(port_num, i2c_addr);
    wiringPiSetup();

    pinMode(port_num + 1, OUTPUT);
    digitalWrite(port_num + 1, 0);
    pinMode(port_num + 3, OUTPUT);
    digitalWrite(port_num + 3, 1);

    fd = lcdInit(2, 16, 4, port_num, port_num + 2, port_num + 4, port_num + 5, port_num + 6, port_num + 7, 0, 0, 0, 0);
    lcdHome(fd);
}

void LCD::clear()
{
    lcdClear(fd);
}

void LCD::showData(float out_temp, float out_hum, float in_temp, float in_hum)
{
    char t1[5];
    char t2[5];
    string str;

    lcdHome(fd);

    snprintf(t1, 4, "%.1f", out_temp);
    snprintf(t2, 4, "%.1f", in_temp);
    str = "TU:" + string(t1) + " TD:" + string(t2);

    lcdPuts(fd, str.c_str());
    lcdPosition(fd, 0, 2);

    snprintf(t1, 4, "%.1f", out_hum);
    snprintf(t2, 4, "%.1f", in_hum);
    str = "HU:" + string(t1) + " HD:" + string(t2);

    lcdPuts(fd, str.c_str());
}
