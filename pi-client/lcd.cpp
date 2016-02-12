#include "lcd.h"
#include <pcf8574.h>
#include <wiringPi.h>
#include <lcd.h>


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
