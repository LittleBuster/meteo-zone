#include "sender.h"


Sender::Sender(shared_ptr<ITcpSocket> client, shared_ptr<ILog> log)
{
    this->m_client = client;
    this->m_log = log;
}

void Sender::start(unsigned seconds)
{
    /*if (this->timer)
        this->timer.reset();*/
    this->timer = make_shared<deadline_timer>(io, boost::posix_time::seconds(seconds));
    this->timer->async_wait(boost::bind(&Sender::send, this));
}

void Sender::send(void)
{
    cout << "lol" << endl;
}
