#pragma once

namespace nashira {
    class NetworkServer {
    public:
        // ---- App flow ----
        static bool try_init(const char* app_id);
        static void update();
        static void shutdown();

        
    };
}
