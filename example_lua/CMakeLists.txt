cmake_minimum_required(VERSION 3.0)

project(xqseme VERSION 0.0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++ -mmacosx-version-min=10.8")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -headerpad_max_install_names")
endif()

set(nlohmann_json_REQUIRED_VERSION 3.2.0)
set(xtl_REQUIRED_VERSION 0.7)
set(cppzmq_REQUIRED_VERSION 4.4.1)
set(zeromq_REQUIRED_VERSION 4.3.2)
# set(CMAKE_C_FLAGS "lrt")

find_package(Qt5Core ${Qt5_REQUIRED_VERSION} REQUIRED)
find_package(Qt5Widgets ${Qt5_REQUIRED_VERSION} REQUIRED)
find_package(xeus ${xeus_REQUIRED_VERSION} REQUIRED)
find_package(nlohmann_json ${nlohmann_json_REQUIRED_VERSION} REQUIRED)
find_package(xtl ${xtl_REQUIRED_VERSION} REQUIRED)
find_package(cppzmq ${cppzmq_REQUIRED_VERSION} REQUIRED)
find_package(xeus-lua REQUIRED)
find_package(xwidgets REQUIRED)
find_package(xproperty REQUIRED)
find_package(xq REQUIRED)
find_package(zeromq ${zeromq_REQUIRED_VERSION} QUIET)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Sources
file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")
file(GLOB UI_SOURCES "*.ui")

qt5_wrap_ui(UI_HEADERS ${UI_SOURCES})

if(WIN32)
    set(APP_ICON ${CMAKE_CURRENT_SOURCE_DIR}/icon.rc)
elseif(APPLE)
    set(MACOSX_BUNDLE_ICON icon.icns)
    set(APP_ICON ${CMAKE_CURRENT_SOURCE_DIR}/icon.icns)
    set_source_files_properties(${APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif()

if(WIN32)
    set(APP_BUNDLE WIN32)
elseif(APPLE)
    set(APP_BUNDLE MACOSX_BUNDLE)
endif()

add_executable(${PROJECT_NAME} ${APP_BUNDLE} ${APP_ICON} ${SOURCES} ${HEADERS} ${UI_HEADERS})

if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/AppleInfo.plist)
endif()

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC ${CPPZMQ_TARGET_NAME}
    PUBLIC nlohmann_json::nlohmann_json
    PUBLIC xtl
    PUBLIC xeus
    PUBLIC xwidgets
    PUBLIC xproperty
    PUBLIC xeus-lua
    PUBLIC Qt5::Core
    PUBLIC Qt5::Widgets
    PUBLIC xq
)

#MacOS bug https://github.com/lloyd/yajl/issues/201
install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION bin)
