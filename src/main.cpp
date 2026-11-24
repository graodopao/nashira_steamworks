#include "network_server.h"
#include "person_and_people.h"

int main() {
    if (nashira::NetworkServer::try_init("480")) {
        printf("Hello, %s!\n", nashira::me().name.c_str());

        printf("Here are your friends: \n");
        for (const nashira::Person& my_friend : nashira::get_friends_list()) {
            printf("%s\n", std::format("{} is {}", my_friend.name, my_friend.user_status).c_str());
        }
    }

    nashira::NetworkServer::shutdown();


    return 0;
}
