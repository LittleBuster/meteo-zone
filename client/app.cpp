#include "app.h"

App::App(shared_ptr<ISender> sender, shared_ptr<IConfigs> cfg, shared_ptr<ILog> log)
{
    m_sender = sender;
    m_cfg = cfg;
    m_log = log;
}

int App::start(void)
{
    m_sender->start(1);
    for (;;) {

    }
}
