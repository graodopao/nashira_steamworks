#include <steam/steam_api.h>
#include "network_server.h"

#include <cstdlib>

#include "user_server.h"

namespace nashira {

    // --- Program Flow ---

    /// Tries to initiate Steamworks. If returning false for any reason, you should exit your app
    bool NetworkServer::try_init(const char* app_id) {
        if (SteamAPI_RestartAppIfNecessary(k_uAppIdInvalid)) {
            return false;
        }

        setenv("SteamAppId", app_id, 1);

        SteamErrMsg error_message{};
        if (SteamAPI_InitEx(&error_message) != k_ESteamAPIInitResult_OK) {
            fprintf(stderr, "Steamworks Initialization Error: %s", error_message);
            return false;
        }

        UserServer::init();

        return true;
    }

    void NetworkServer::update() {
        SteamAPI_RunCallbacks();
    }

    void NetworkServer::shutdown() {
        SteamAPI_Shutdown();
    }
}
