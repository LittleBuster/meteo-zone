#ifndef __APP_H__
#define __APP_H__

#include "sender.h"
#include "configs.h"
#include "log.h"

class App
{
private:
    shared_ptr<ISender> m_sender;
    shared_ptr<IConfigs> m_cfg;
    shared_ptr<ILog> m_log;

public:
    App(shared_ptr<ISender> sender, shared_ptr<IConfigs> cfg, shared_ptr<ILog> log);

    int start(void);
};


#endif
