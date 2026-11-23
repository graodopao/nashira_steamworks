#include "user_server.h"

#include <numeric>
#include <steam/isteamfriends.h>
#include <steam/isteamuser.h>
#include <ranges>

namespace nashira {
    // Properties
    UserServer::Person UserServer::me{};

    namespace {
        // -- TO STEAM --
        CSteamID to_steam(const std::uint64_t id) {
            return {static_cast<uint64>(id)};
        }

        // -- FROM STEAM --
        UserServer::UserStatus from_steam(const EPersonaState state) {
            switch (state) {
                case k_EPersonaStateOffline:
                case k_EPersonaStateInvisible:
                case k_EPersonaStateMax:
                    return UserServer::UserStatus::OFFLINE;
                case k_EPersonaStateOnline:
                case k_EPersonaStateLookingToTrade:
                case k_EPersonaStateLookingToPlay:
                    return UserServer::UserStatus::ONLINE;
                case k_EPersonaStateBusy:
                    return UserServer::UserStatus::BUSY;
                case k_EPersonaStateAway:
                case k_EPersonaStateSnooze:
                    return UserServer::UserStatus::AWAY;
            }

            return UserServer::UserStatus::OFFLINE;
        }
    }

    // Functions
    void UserServer::init() {
        me = get_user_info(SteamUser()->GetSteamID().ConvertToUint64());
    }


    UserServer::Person UserServer::get_user_info(const uint64_t user_id) {
        return Person {
            .name = SteamFriends()->GetFriendPersonaName(to_steam(user_id)),
            .steam_id = user_id,
            .user_status = from_steam(SteamFriends()->GetFriendPersonaState(to_steam(user_id)))
        };
    }

    UserServer::People UserServer::get_friends_list() {
        People friends {};

        const int friends_count { SteamFriends()->GetFriendCount(k_EFriendFlagImmediate) };
        friends.users.reserve(friends_count);

        for (int index : std::views::iota(0, friends_count)) {

        }
    }

    void UserServer::update() {

    }

    // ---- PEOPLE ----

    void UserServer::People::update() const {
        bool any_updated{false};

        for (Person user: users) {
            const UserStatus status { from_steam(SteamFriends()->GetFriendPersonaState(to_steam(user.steam_id))) };

            if (user.user_status != status) {
                user.user_status = status;
                any_updated = true;
            }
        }

        if (any_updated) {
            // Do a callback
        }
    }
}
