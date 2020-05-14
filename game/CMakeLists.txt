# Project Info
set(PROJECT_NAME_CODE "gameoflife")
set(PROJECT_NAME_FULL "Game of Life")
set(PROJECT_BUNDLE_IDENTIFIER "com.timmendenhall.${PROJECT_NAME_CODE}")
project("${PROJECT_NAME_CODE}")

set(MAJOR_VERSION 1)
set(MINOR_VERSION 0)
set(PATCH_VERSION 0)
set(FULL_VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")

# Create our executable target
set(HEADER_FILES
    include/Application.h
    include/Cell.h
    )

set(SOURCE_FILES
    src/main.cpp
    src/Application.cpp
    src/Cell.cpp
    )

# For Apple set the icns file containing icons, copy frameworks
if(APPLE)
    # set how it shows up in the Info.plist file
    set(MACOSX_BUNDLE_ICON_FILE Icon.icns)
    set(MACOSX_BUNDLE_INFO_STRING "Jon Conway's Game of Life programmed in C++ using SFML.")
    set(MACOSX_BUNDLE_COPYRIGHT "Copyright 2020, Tim Mendenhall. All Rights Reserved.")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "${FULL_VERSION}")
    set(MACOSX_BUNDLE_BUNDLE_NAME "${PROJECT_NAME_FULL}")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "${PROJECT_BUNDLE_IDENTIFIER}")

    # set where in the bundle to put the icns file
    set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/osx/Icon.icns
        PROPERTIES MACOSX_PACKAGE_LOCATION Resources
    )

    # adding the icon to the sources
    set(SOURCE_FILES ${SOURCE_FILES} osx/Icon.icns)

endif(APPLE)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

if (APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        RESOURCE "${RESOURCE_FILES}"
        )
endif(APPLE)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Link Libraries
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio dream)

# Note OSX Specific extension .app
set(APPS "\${CMAKE_BINARY_DIR}/game/${PROJECT_NAME}.app")

# Directories to look for dependencies
set(DIRS "${CMAKE_INSTALL_PREFIX}/lib")
message("hi ${DIRS}")

# otherwise app goes to /usr/local/{app name}
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

install(CODE "include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")")

include(CPack)