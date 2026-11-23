#include <steam/steam_api.h>
#include "network_server.h"

#include <functional>
#include <stdlib.h>

namespace nashira {

    bool NetworkServer::try_init(const char* app_id) {
        setenv("SteamAppId", app_id, 1);

        SteamErrMsg error_message{};
        if (SteamAPI_InitEx(&error_message) != k_ESteamAPIInitResult_OK) {
            fprintf(stderr, "Steamworks Initialization Error: %s", error_message);
            return false;
        }

        return true;
    }
}
