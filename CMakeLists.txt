#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.9)


# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project(mercer VERSION 0.0.1 DESCRIPTION "This library provides helping functions for building SFML projects")

# Set version information in a config.h file
set(myproject_VERSION_MAJOR 1)
set(myproject_VERSION_MINOR 0)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
set(LIBRARY_NAME "mercer")
add_library(${LIBRARY_NAME} SHARED
  src/FileUtils.cpp
  src/Seek.cpp
  src/StringUtils.cpp
  src/VectorUtils.cpp
)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${LIBRARY_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

target_include_directories( ${LIBRARY_NAME} PRIVATE include)

set(PUBLIC_INTERFACE)
list(APPEND PUBLIC_INTERFACE
  mercer/AI/Steering/Seek.hpp
  mercer/AI/BaseEntity.hpp
  mercer/AI/State.hpp
  mercer/Misc/FileUtils.hpp
  mercer/Misc/NonCopyable.hpp
  mercer/Misc/NumberUtils.hpp
  mercer/Misc/StringUtils.hpp
  mercer/Misc/VectorUtils.hpp
  mercer/Resources/ResourceHolder.hpp
  mercer/Service/BaseService.hpp
  mercer/Service/MessageQueue.hpp
  mercer/Service/ServiceProvider.hpp
)

# Install target
#install(TARGETS ${LIBRARY_NAME} DESTINATION bin)
set_target_properties( ${LIBRARY_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties( ${LIBRARY_NAME} PROPERTIES FRAMEWORK       FALSE
                                                  PUBLIC_HEADER   "${PUBLIC_INTERFACE}"
)

include(GNUInstallDirs)

install(DIRECTORY include DESTINATION .)

install(TARGETS         ${LIBRARY_NAME}
        LIBRARY         DESTINATION   ${CMAKE_INSTALL_LIBDIR}
#        PUBLIC_HEADER   DESTINATION   ${CMAKE_INSTALL_INCLUDEDIR}
)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${myproject_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${myproject_VERSION_MINOR}")
include(CPack)