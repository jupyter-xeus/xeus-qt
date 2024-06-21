cmake_minimum_required(VERSION 3.0)

project(xeus-qt VERSION 0.0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

if (NOT DEFINED XEUS_QT_EXECUTABLE)
    set(XEUS_QT_EXECUTABLE "${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}")
endif ()

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/../share/jupyter/kernels/xq/kernel.json.in
    ${CMAKE_CURRENT_BINARY_DIR}/share/jupyter/kernels/xq/kernel.json
)

configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/../share/jupyter/kernels/xq/logo-32x32.png"
    "${CMAKE_CURRENT_BINARY_DIR}/share/jupyter/kernels/xq/"
    COPYONLY
)

configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/../share/jupyter/kernels/xq/logo-64x64.png"
    "${CMAKE_CURRENT_BINARY_DIR}/share/jupyter/kernels/xq/"
    COPYONLY
)

#if(APPLE)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++ -mmacosx-version-min=10.8")
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -headerpad_max_install_names")
#endif()

set(nlohmann_json_REQUIRED_VERSION 3.11.3)
# set(CMAKE_C_FLAGS "lrt")

find_package(Qt5Core ${Qt5_REQUIRED_VERSION} REQUIRED)
find_package(Qt5Widgets ${Qt5_REQUIRED_VERSION} REQUIRED)
find_package(nlohmann_json ${nlohmann_json_REQUIRED_VERSION} REQUIRED)
find_package(xeus-lua REQUIRED)
find_package(xwidgets REQUIRED)
find_package(xproperty REQUIRED)
find_package(xq REQUIRED)
find_package(xcanvas REQUIRED)

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
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/AppleInfo.plist)
endif()

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC nlohmann_json::nlohmann_json
    PUBLIC xeus-lua
    PUBLIC xwidgets
    PUBLIC xproperty
    PUBLIC Qt5::Core
    PUBLIC Qt5::Widgets
    PUBLIC xq
)

install(
    DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/share/jupyter/kernels/xq/
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/jupyter/kernels/xq
)

#MacOS bug https://github.com/lloyd/yajl/issues/201
install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION bin)