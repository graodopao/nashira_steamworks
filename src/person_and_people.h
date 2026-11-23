#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace nashira {
    enum class UserStatus {
        OFFLINE,
        ONLINE,
        BUSY,
        AWAY,
    };

    struct Person {
        std::string name{};
        uint64_t steam_id{};
        UserStatus user_status{};
    };

    struct People {
        std::vector<Person> users;

        bool try_and_update();
        void invite_all() const;

        auto begin() { return users.begin(); }
        auto end() { return users.end(); }
        [[nodiscard]] auto begin() const { return users.begin(); }
        [[nodiscard]] auto end() const { return users.end(); }
    };

    // --- Utils ---
    static Person me();
    static Person get_person(uint64_t user_id);
    static People get_friends_list();

}
