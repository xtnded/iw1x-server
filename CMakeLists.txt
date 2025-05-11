cmake_minimum_required(VERSION 3.10)

project(iw1x-server)

set(SEPARATOR "---------------------")

# -m32:     32-bit
# -fpic:    Position-independent code
# -Wall:    Enable all warnings
# -fvisibility=hidden: Hide symbols
set(CMAKE_CXX_FLAGS "-m32 -fpic -Wall -fvisibility=hidden")
set(CMAKE_SHARED_LINKER_FLAGS "-m32")
set(CMAKE_LIBRARY_PATH "/lib32" "/usr/lib32" "/usr/lib/i386-linux-gnu" ${CMAKE_LIBRARY_PATH})

# Options
option(DEBUG_BUILD "Include debug info, no optimization" OFF)
option(ENABLE_UNSAFE "Enable risky features (fread, fwrite...)" OFF)
option(COMPILE_SSL "SSL support" OFF)
option(COMPILE_CURL "cURL support" OFF)
option(COMPILE_SQLITE "SQLite support" OFF)

message(STATUS "${SEPARATOR}")
message(STATUS "Debug: ${DEBUG_BUILD}")
message(STATUS "Risky features: ${ENABLE_UNSAFE}")
message(STATUS "SSL: ${COMPILE_SSL}")
message(STATUS "cURL: ${COMPILE_CURL}")
message(STATUS "SQLite: ${COMPILE_SQLITE}")
message(STATUS "${SEPARATOR}")

# -g:       Include debug info
# -ggdb:    Debug info for gdb
# -O2:      Moderate optimization
if(DEBUG_BUILD)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb")
else()
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

if(ENABLE_UNSAFE)
    add_definitions(-DENABLE_UNSAFE=1)
else()
    add_definitions(-DENABLE_UNSAFE=0)
endif()

if(COMPILE_SQLITE)
    find_library(SQLITE_LIB sqlite3)
    if(SQLITE_LIB)
        add_definitions(-DCOMPILE_SQLITE=1)
        set(SQLITE_FOUND TRUE)
    else()
        message(FATAL_ERROR "SQLite requested but library not found.")
    endif()
else()
    add_definitions(-DCOMPILE_SQLITE=0)
endif()

if(COMPILE_CURL)
    find_library(CURL_LIB curl)
    if(CURL_LIB)
        add_definitions(-DCOMPILE_CURL=1)
        set(CURL_FOUND TRUE)
    else()
        message(FATAL_ERROR "cURL requested but library not found.")
    endif()
else()
    add_definitions(-DCOMPILE_CURL=0)
endif()

if(COMPILE_SSL)
    add_definitions(-DCOMPILE_SSL=1)
    find_package(OpenSSL REQUIRED)
else()
    add_definitions(-DCOMPILE_SSL=0)
endif()

# Source files
set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/hook.cpp
    ${CMAKE_SOURCE_DIR}/src/iw1x.cpp
    ${CMAKE_SOURCE_DIR}/src/gsc.cpp
    ${CMAKE_SOURCE_DIR}/src/gsc_entity.cpp
    ${CMAKE_SOURCE_DIR}/src/gsc_player.cpp
    ${CMAKE_SOURCE_DIR}/src/gsc_bots.cpp
    ${CMAKE_SOURCE_DIR}/src/gsc_weapons.cpp
    ${CMAKE_SOURCE_DIR}/src/gsc_exec.cpp
    ${CMAKE_SOURCE_DIR}/src/gsc_utils.cpp
    ${CMAKE_SOURCE_DIR}/src/jump.cpp
)

if(SQLITE_FOUND)
    list(APPEND SOURCES ${CMAKE_SOURCE_DIR}/src/gsc_sqlite.cpp)
endif()

if(CURL_FOUND)
    list(APPEND SOURCES ${CMAKE_SOURCE_DIR}/src/gsc_curl.cpp)
endif()

add_library(iw1x SHARED ${SOURCES})
target_precompile_headers(iw1x PRIVATE ${CMAKE_SOURCE_DIR}/src/pch.h)

# Output properties
set_target_properties(iw1x PROPERTIES
    OUTPUT_NAME "iw1x"
    PREFIX ""
    SUFFIX ".so"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

# Linked libraries
target_link_libraries(iw1x
    dl
    pthread
)

if(SQLITE_FOUND)
    target_link_libraries(iw1x ${SQLITE_LIB})
endif()

if(CURL_FOUND)
    target_link_libraries(iw1x ${CURL_LIB})
endif()

if(COMPILE_SSL)
    target_link_libraries(iw1x OpenSSL::SSL OpenSSL::Crypto)
endif()