#include "person_and_people.h"

#include <steam/isteamfriends.h>
#include <steam/isteamuser.h>
#include <ranges>

namespace nashira {
    namespace {
        // -- TO STEAM --
        CSteamID to_steam(const std::uint64_t id) {
            return {static_cast<uint64>(id)};
        }

        // -- FROM STEAM --
        USER_STATUS from_steam(const EPersonaState state) {
            switch (state) {
                case k_EPersonaStateOffline:
                case k_EPersonaStateInvisible:
                case k_EPersonaStateMax:
                    return USER_STATUS::OFFLINE;
                case k_EPersonaStateOnline:
                case k_EPersonaStateLookingToTrade:
                case k_EPersonaStateLookingToPlay:
                    return USER_STATUS::ONLINE;
                case k_EPersonaStateBusy:
                    return USER_STATUS::BUSY;
                case k_EPersonaStateAway:
                case k_EPersonaStateSnooze:
                    return USER_STATUS::AWAY;
            }

            return USER_STATUS::OFFLINE;
        }
    }

    Person me() {
        return get_person(SteamUser()->GetSteamID().ConvertToUint64());
    }

    Person get_person(const uint64_t user_id) {
        return Person {
            .name = SteamFriends()->GetFriendPersonaName(to_steam(user_id)),
            .steam_id = user_id,
            .user_status = from_steam(SteamFriends()->GetFriendPersonaState(to_steam(user_id)))
        };
    }

    People get_friends_list() {
        const int friends_count { SteamFriends()->GetFriendCount(k_EFriendFlagImmediate) };
        People friends {};
        if (friends_count == -1) {
            return friends;
        }

        friends.users.reserve(friends_count);

        for (const int index : std::views::iota(0, friends_count)) {
            friends.users.push_back(get_person(SteamFriends()->GetFriendByIndex(index, k_EFriendFlagImmediate).ConvertToUint64()));
        }

        return friends;
    }


    // ---- PEOPLE ----

    // Checks and updates people in the list. Returns true if some any changed, false otherwise
    bool People::try_and_update() {
        bool any_updated{false};

        for (Person& user: users) {
            const USER_STATUS status { from_steam(SteamFriends()->GetFriendPersonaState(to_steam(user.steam_id))) };

            if (user.user_status != status) {
                user.user_status = status;
                any_updated = true;
            }
        }

        return any_updated;
    }

    void People::invite_all() const {
        // TODO
    }
}
