#include "sender.h"


Sender::Sender(shared_ptr<ITcpSocket> client, shared_ptr<IConfigs> cfg, shared_ptr<ILog> log)
{
    this->m_client = client;
    this->m_cfg = cfg;
    this->m_log = log;
}

void Sender::start(void)
{
    this->timer = make_shared<deadline_timer>(io, boost::posix_time::seconds(this->interval));
    this->timer->async_wait(boost::bind(&Sender::send, this));
    io.run();
}

void Sender::send(void)
{
    auto msc = m_cfg->getMeteoCfg();

    try {
        this->m_client->connect(msc->ip, msc->port);
        this->m_client->close();
    }
    catch (const string &err) {
        m_log->local("[CLIENT]: " + err, LOG_ERROR);
    }

    timer->expires_at(timer->expires_at() + boost::posix_time::seconds(this->interval));
    this->timer->async_wait(boost::bind(&Sender::send, this));
}
