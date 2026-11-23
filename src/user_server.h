#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace nashira {
    class UserServer {
    public:
        enum class UserStatus {
            OFFLINE,
            ONLINE,
            BUSY,
            AWAY,
        };

        struct Person {
            std::string name;
            uint64_t steam_id;
            UserStatus user_status;
        };

        struct People {
            std::vector<Person> users;
            void update() const;
        };

        static Person me;

        // --- Flow ---
        static void init();
        static void update();

        // --- Utils ---
        static Person get_user_info(uint64_t user_id);

        static People get_friends_list();
    };


}
