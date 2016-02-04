#ifndef __SENDER_H__
#define __SENDER_H__

#include "tcpsocket.h"
#include "configs.h"
#include "log.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::asio;


class ISender
{
public:
    virtual void setInterval(unsigned seconds) = 0;
    virtual void start(void) = 0;
};


class Sender: public ISender
{
private:
    shared_ptr<ITcpSocket> m_client;
    shared_ptr<IConfigs> m_cfg;
    shared_ptr<ILog> m_log;
    io_service io;
    shared_ptr<deadline_timer> timer;
    unsigned interval;

    void send(void);

public:
    Sender(shared_ptr<ITcpSocket> client, shared_ptr<IConfigs> cfg, shared_ptr<ILog> log);

    inline void setInterval(unsigned seconds) {
        this->interval = seconds;
    }

    void start(void);
};


#endif
