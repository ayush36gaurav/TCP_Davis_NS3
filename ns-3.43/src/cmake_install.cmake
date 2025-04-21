# Install script for directory: /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/antenna/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/aodv/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/applications/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/bridge/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/brite/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/buildings/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/click/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/config-store/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/core/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/csma/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/csma-layout/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsdv/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/dsr/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/energy/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/fd-net-device/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/flow-monitor/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/internet/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/internet-apps/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/lr-wpan/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/lte/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mesh/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/mobility/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/netanim/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/nix-vector-routing/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/olsr/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/openflow/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/point-to-point/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/point-to-point-layout/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/propagation/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/sixlowpan/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/spectrum/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/stats/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/tap-bridge/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/topology-read/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/traffic-control/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/uan/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/virtual-net-device/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/wifi/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/wimax/cmake_install.cmake")

endif()

