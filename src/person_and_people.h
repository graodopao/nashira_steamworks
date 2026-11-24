#pragma once
#include <cstdint>
#include <format>
#include <string>
#include <vector>
#include <ostream>
#include <format>
#include <string_view>

#include "network_server.h"



namespace nashira {
    enum class USER_STATUS {
        OFFLINE,
        ONLINE,
        BUSY,
        AWAY,
    };

    constexpr const char* to_string(const USER_STATUS status) {
        switch (status) {
            case USER_STATUS::OFFLINE: return "Offline";
            case USER_STATUS::ONLINE: return "Online";
            case USER_STATUS::BUSY: return "Busy";
            case USER_STATUS::AWAY: return "Away";
        }

        return "Unknown";
    }

    inline std::ostream& operator<<(std::ostream& os, const USER_STATUS status) {
        return os << to_string(status);
    }

    struct Person {
        std::string name{};
        uint64_t steam_id{};
        USER_STATUS user_status{};
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
    Person me();
    Person get_person(uint64_t user_id);
    People get_friends_list();

}


template <>
struct std::formatter<nashira::USER_STATUS> : std::formatter<std::string_view> {
    auto format(const nashira::USER_STATUS status, std::format_context& context) const {
        return std::formatter<std::string_view>::format(nashira::to_string(status), context);
    }
};