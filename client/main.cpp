#include <memory>
#include "app.h"
#include "configs.h"
#include "log.h"
#include "sender.h"
#include "tcpsocket.h"


int main(int argc, char *argv[])
{
    auto cfg = make_shared<Configs>();
    auto client = make_shared<TcpSocket>();
    auto log = make_shared<Log>(client);
    auto sender = make_shared<Sender>(client, log);

    auto app = make_shared<App>(sender, cfg, log);
    return app->start();
}
