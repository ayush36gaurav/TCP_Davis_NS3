# Install script for directory: /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-mobility-debug.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-mobility-debug.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-mobility-debug.so"
         RPATH "/usr/local/lib:$ORIGIN/:$ORIGIN/../lib:/usr/local/lib64:$ORIGIN/:$ORIGIN/../lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/lib/libns3.43-mobility-debug.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-mobility-debug.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-mobility-debug.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-mobility-debug.so"
         OLD_RPATH "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/lib::::::::::::::::::::::::::::"
         NEW_RPATH "/usr/local/lib:$ORIGIN/:$ORIGIN/../lib:/usr/local/lib64:$ORIGIN/:$ORIGIN/../lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-mobility-debug.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ns3" TYPE FILE FILES
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/helper/group-mobility-helper.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/helper/mobility-helper.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/helper/ns2-mobility-helper.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/box.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/constant-acceleration-mobility-model.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/constant-position-mobility-model.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/constant-velocity-helper.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/constant-velocity-mobility-model.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/gauss-markov-mobility-model.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/geocentric-constant-position-mobility-model.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/geographic-positions.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/hierarchical-mobility-model.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/mobility-model.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/position-allocator.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/random-direction-2d-mobility-model.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/random-walk-2d-mobility-model.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/random-waypoint-mobility-model.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/rectangle.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/steady-state-random-waypoint-mobility-model.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/waypoint-mobility-model.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/model/waypoint.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/include/ns3/mobility-module.h"
    )
endif()

