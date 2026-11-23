#include "network_server.h"
#include "user_server.h"

int main() {
    if (nashira::NetworkServer::try_init("480")) {
        printf("Hello, %s!", nashira::UserServer::me.name.c_str());
    }

    nashira::NetworkServer::shutdown();


    return 0;
}
