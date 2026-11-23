#include "network_server.h"
#include "person_and_people.h"

int main() {
    if (nashira::NetworkServer::try_init("480")) {
        printf("Hello, %s!", nashira::UserServer::me.name.c_str());
    }

    nashira::NetworkServer::shutdown();


    return 0;
}
