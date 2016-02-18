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

#ifndef __LCD_H__
#define __LCD_H__


class ILCD
{
public:
    virtual void init(unsigned port_num, unsigned i2c_addr) = 0;
    virtual void clear(void) const = 0;
    virtual void showData(float out_temp, float out_hum, float in_temp, float in_hum) = 0;
};


class LCD: public ILCD
{
private:
    int fd;

public:
    /**
     * Display initialization
     * @port_num: set extended GPIO number
     * @i2c_addr: disply i2c-bus address
     */
    void init(unsigned port_num, unsigned i2c_addr);

    /*
     * Clear display
     */
    void clear(void) const;

    /*
     * Show meteo information
     */
    void showData(float out_temp, float out_hum, float in_temp, float in_hum);
};


#endif
