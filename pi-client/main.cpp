#include <memory>
#include "app.h"
#include "configs.h"
#include "log.h"
#include "sender.h"
#include "tcpsocket.h"


int main(void)
{
    auto cfg = make_shared<Configs>();
    auto client = make_shared<TcpSocket>();
    auto log = make_shared<Log>(client);
    auto sender = make_shared<Sender>(client, cfg, log);

    auto app = make_shared<App>(sender, cfg, log);
    return app->start();
}
