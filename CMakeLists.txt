cmake_minimum_required(VERSION 3.20)  # CMake version check
project(nashira_steamworks)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 20)


set (STEAMWORKS_SDK_DIR "/home/trigo/Downloads/steamworks/sdk/" CACHE PATH "Path to the Steamworks SDK 'sdk' folder")

if (NOT EXISTS "${STEAMWORKS_SDK_DIR}/public/steam/steam_api.h")
    message(FATAL_ERROR "Steamworks SDK not found! Pass -DSTEAMWORKS_SDK_DIR=/path/to/sdk")
endif()

add_library(steamworks_sdk SHARED IMPORTED)
target_include_directories(steamworks_sdk INTERFACE "${STEAMWORKS_SDK_DIR}/public")

if (WIN32)
    set_target_properties(steamworks_sdk PROPERTIES IMPORTED_LOCATION "${STEAMWORKS_SDK_DIR}/redistributable_bin/win64/steam_api64.dll" IMPORTED_IMPLIB "${STEAMWORKS_SDK_DIR}/redistributable_bin/win64/steam_api64.lib")
elseif(APPLE)
    set_target_properties(steamworks_sdk PROPERTIES IMPORTED_LOCATION "${STEAMWORKS_SDK_DIR}/redistributable_bin/osx/libsteam_api.dylib")
else()
    set_target_properties(steamworks_sdk PROPERTIES IMPORTED_LOCATION "${STEAMWORKS_SDK_DIR}/redistributable_bin/linux64/libsteam_api.so")
endif()


# Add main.cpp file of the project root directory as a source file
set(SOURCE_FILES src/main.cpp
        src/network_server.cpp
        src/network_server.h
        src/user_server.cpp
        src/user_server.h)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(nashira_steamworks ${SOURCE_FILES})
target_link_libraries(nashira_steamworks PRIVATE steamworks_sdk)
