#ifndef __LCD_H__
#define __LCD_H__


class ILCD
{
public:
    virtual void init(unsigned port_num, unsigned i2c_addr) = 0;
    virtual void clear(void) = 0;
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
    void clear(void);

    /*
     * Show meteo information
     */
    void showData(float out_temp, float out_hum, float in_temp, float in_hum);
};


#endif
