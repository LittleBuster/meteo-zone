#ifndef __SENDER_H__
#define __SENDER_H__

#include "tcpsocket.h"
#include "log.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::asio;


class ISender
{
public:
    virtual void start(unsigned seconds) = 0;
    virtual void send(void) = 0;
};


class Sender: public ISender
{
private:
    shared_ptr<ITcpSocket> m_client;
    shared_ptr<ILog> m_log;
    io_service io;
    shared_ptr<deadline_timer> timer;

public:
    Sender(shared_ptr<ITcpSocket> client, shared_ptr<ILog> log);

    void start(unsigned seconds);

    void send(void);
};


#endif
