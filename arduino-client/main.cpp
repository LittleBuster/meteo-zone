/* Meteo-Zone Arduino application
 *
 * Copyright (C) 2015 Sergey Denisov.
 * Rewritten by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>
#include "EtherCard.h"
#include "dht22.h"
#include "ds18b20.h"
#include "lcd1602.h"
#include "i2c.h"


static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[700];
static uint32_t timer;

struct dht22 dht_out;
struct ds18b20 ds;

const char website[] PROGMEM = "www.galynsky.ru";

void reverse(char *str, int len)
{
    int8_t i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

int int_to_str(int x, char str[], int8_t d)
{
    uint8_t i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }
    
    while (i < d)
        str[i++] = '0';
 
    reverse(str, i);
    str[i] = '\0';
    return i;
}

void ftoa(float n, char *res, int8_t afterpoint)
{
    int ipart = (int8_t)n;
    float fpart = n - (float)ipart;
 
    int i = int_to_str(ipart, res, 0);
    if (afterpoint != 0)
    {
        res[i] = '.';
        fpart = fpart * pow(10, afterpoint);
        int_to_str((int8_t)fpart, res + i + 1, afterpoint);
    }
}

static void my_callback (uint8_t status,uint16_t off,uint16_t len)
{
  Ethernet::buffer[off+300] = 0;
}

void setup ()
{
  Serial.begin(9600);
  Serial.println(F("\n[webClient]"));

  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println(F("Failed to access Ethernet controller"));
  if (!ether.dhcpSetup())
    Serial.println(F("DHCP failed"));

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);  

  if (!ether.dnsLookup(website))
    Serial.println("DNS failed");
    
  ether.printIp("SRV: ", ether.hisip);
  dht_init(&dht_out, 1);
  ds18b20_init(&ds, 2);
  lcd1602_init();
  lcd1602_clear();
  
  DDRD |= (1 << 2);
  PORTD &= ~(1 << 2);
  
  lcd1602_send_string("   Meteo-Zone   ");
  lcd1602_goto_xy(0, 1);
  lcd1602_send_string("      2016      ");
  delay(2000);
}

void loop ()
{
  ether.packetLoop(ether.packetReceive());
  
  if (millis() > timer) {
	if (!ether.dnsLookup(website))
	    Serial.println("DNS failed");

    timer = millis() + 5000;
    Serial.println();
    
    float temp, hum;
    char lcd_line[24];
    int8_t in_temp;
    
    dht_read_data(&dht_out, &temp, &hum);
    //ds18b20_read_temp(&ds, &in_temp);
    
    char data[20];
    char out[50];
    
    ftoa(temp, data, 2);
    strcpy(out, "{\"Id\": 10000001, \"Temp\": ");
    strcat(out, data);
    strcpy(lcd_line, "T:");
    strcat(lcd_line, data);
    strcat(lcd_line, "  H:");   
    
    strcat(out, ", \"Hum\": ");
    ftoa(hum, data, 2);
    strcat(out, data);
    strcat(out, "}");
    strcat(lcd_line, data);
    strcat(lcd_line, "%");
    lcd1602_clear();
    lcd1602_send_string(lcd_line);
    
    lcd1602_goto_xy(0, 1);
    strcpy(lcd_line, "     InT:");
    sprintf(data, "%d", in_temp);
    strcat(lcd_line, data);
    lcd1602_send_string(lcd_line);
    
    Serial.println(out);
    ether.sendTCP(website, out, my_callback, 6000);
    //ether.httpPost(PSTR("/meteo/"), website, "additional", out, my_callback);
    
    PORTD |= (1 << 2);
    _delay_ms(500);
    PORTD &= ~(1 << 2);
    _delay_ms(500);
    PORTD |= (1 << 2);
    _delay_ms(500);
    PORTD &= ~(1 << 2);
    _delay_ms(500);
  }
}
