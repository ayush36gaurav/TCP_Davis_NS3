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
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/antenna/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/aodv/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/applications/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/bridge/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/brite/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/buildings/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/click/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/config-store/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/core/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/csma/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/csma-layout/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/dsdv/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/dsr/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/energy/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/fd-net-device/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/flow-monitor/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/internet/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/internet-apps/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/lr-wpan/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/lte/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/mesh/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/mobility/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/netanim/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/network/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/nix-vector-routing/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/olsr/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/openflow/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/point-to-point/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/point-to-point-layout/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/propagation/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/sixlowpan/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/spectrum/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/stats/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/tap-bridge/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/topology-read/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/traffic-control/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/uan/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/virtual-net-device/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/wifi/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/build/src/wimax/cmake_install.cmake")

endif()

