# Install script for directory: /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh

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
    set(CMAKE_INSTALL_CONFIG_NAME "debug")
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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-mesh-debug.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-mesh-debug.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-mesh-debug.so"
         RPATH "/usr/local/lib:$ORIGIN/:$ORIGIN/../lib:/usr/local/lib64:$ORIGIN/:$ORIGIN/../lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/lib/libns3.43-mesh-debug.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-mesh-debug.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-mesh-debug.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-mesh-debug.so"
         OLD_RPATH "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/lib::::::::::::::::::::::::::::"
         NEW_RPATH "/usr/local/lib:$ORIGIN/:$ORIGIN/../lib:/usr/local/lib64:$ORIGIN/:$ORIGIN/../lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-mesh-debug.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ns3" TYPE FILE FILES
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/helper/dot11s/dot11s-installer.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/helper/flame/flame-installer.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/helper/mesh-helper.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/helper/mesh-stack-installer.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/dot11s/dot11s-mac-header.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/dot11s/hwmp-protocol.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/dot11s/hwmp-rtable.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/dot11s/ie-dot11s-beacon-timing.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/dot11s/ie-dot11s-configuration.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/dot11s/ie-dot11s-id.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/dot11s/ie-dot11s-metric-report.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/dot11s/ie-dot11s-peer-management.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/dot11s/ie-dot11s-peering-protocol.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/dot11s/ie-dot11s-perr.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/dot11s/ie-dot11s-prep.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/dot11s/ie-dot11s-preq.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/dot11s/ie-dot11s-rann.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/dot11s/peer-link-frame.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/dot11s/peer-link.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/dot11s/peer-management-protocol.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/flame/flame-header.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/flame/flame-protocol-mac.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/flame/flame-protocol.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/flame/flame-rtable.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/mesh-information-element-vector.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/mesh-l2-routing-protocol.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/mesh-point-device.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/mesh-wifi-beacon.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/mesh-wifi-interface-mac-plugin.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/model/mesh-wifi-interface-mac.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/include/ns3/mesh-module.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/cmake-cache/src/mesh/examples/cmake_install.cmake")

endif()

