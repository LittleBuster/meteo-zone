#include "app.h"
#include <boost/thread.hpp>


App::App(shared_ptr<ISender> sender, shared_ptr<IConfigs> cfg, shared_ptr<ILog> log)
{
    m_sender = sender;
    m_cfg = cfg;
    m_log = log;
}

int App::start(void)
{
    cout << "Starting weather server..." << endl;
    m_log->setLogFile("/var/log/meteo.log");

    try {
        m_cfg->load("/etc/meteo.cfg");
    }
    catch (const string &err) {
        m_log->local("[CONFIGS]: " + err, LOG_ERROR);
        return -1;
    }
    auto msc = m_cfg->getMeteoCfg();
    auto rlc = m_cfg->getRLogCfg();
    m_log->setRemoteLogCfg(rlc->ip, rlc->port);

    m_sender->setInterval(msc->interval);
    m_sender->start();

    for (;;) {
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
}
