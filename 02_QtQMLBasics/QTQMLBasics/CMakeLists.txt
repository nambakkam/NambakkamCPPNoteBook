cmake_minimum_required(VERSION 3.16)

project(QTQMLBasics VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find Qt Dependencies
find_package(Qt6 REQUIRED COMPONENTS Quick)
qt_standard_project_setup(REQUIRES 6.8)

# 2. Define the Target with its main entry point
qt_add_executable(appQTQMLBasics
    src/main.cpp
)

# 3. Configure the QML Module and Source Files
qt_add_qml_module(appQTQMLBasics
    URI QTQMLBasics
    VERSION 1.0
    QML_FILES
        view/Main.qml
    SOURCES
        src/devices/ismartdevice.h
        src/devices/ismartdevice.cpp
        include/deviceenums.h
        src/devices/light.h
        src/devices/light.cpp
        src/room.h
        src/room.cpp
        src/smartdevicefactory.h
        src/smartdevicefactory.cpp
        src/smartdevicemanager.h
        src/smartdevicemanager.cpp
        src/models/devicelistmodel.h
        src/models/devicelistmodel.cpp
        SOURCES src/models/roomsmodel.h src/models/roomsmodel.cpp
        SOURCES src/devices/airconditioner.cpp src/devices/airconditioner.h
)


# 4. Include Directories for clean #include paths in C++
target_include_directories(appQTQMLBasics PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/devices
    ${CMAKE_CURRENT_SOURCE_DIR}/src/models
)

# 5. Link Libraries
target_link_libraries(appQTQMLBasics
    PRIVATE Qt6::Quick
)

# 6. Global App Target Properties (Window/OS specific)
set_target_properties(appQTQMLBasics PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 7. Installation Setup
include(GNUInstallDirs)
install(TARGETS appQTQMLBasics
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
