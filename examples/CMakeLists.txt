cmake_minimum_required(VERSION 3.8)
project(xq_example)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib; ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(nlohmann_json_REQUIRED_VERSION 3.2.0)
set(xtl_REQUIRED_VERSION 0.7)
set(cppzmq_REQUIRED_VERSION 4.4.1)
set(zeromq_REQUIRED_VERSION 4.3.2)

find_package(Qt5Core ${Qt5_REQUIRED_VERSION} REQUIRED)
find_package(Qt5Widgets ${Qt5_REQUIRED_VERSION} REQUIRED)
find_package(xeus ${xeus_REQUIRED_VERSION} REQUIRED)
find_package(nlohmann_json ${nlohmann_json_REQUIRED_VERSION} REQUIRED)
find_package(xtl ${xtl_REQUIRED_VERSION} REQUIRED)
find_package(cppzmq ${cppzmq_REQUIRED_VERSION} REQUIRED)
find_package(xeus-sqlite REQUIRED)
find_package(xq REQUIRED)
find_package(zeromq ${zeromq_REQUIRED_VERSION} QUIET)

add_executable(xq_exe main.cpp)

target_link_libraries(
    xq_exe
    PUBLIC ${CPPZMQ_TARGET_NAME}
    PUBLIC nlohmann_json::nlohmann_json
    PUBLIC xtl
    PUBLIC xeus
    PUBLIC xeus-sqlite
    PUBLIC Qt5::Core
    PUBLIC Qt5::Widgets
    PUBLIC xq
)

install(TARGETS xq_exe
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
