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
    set(CMAKE_INSTALL_CONFIG_NAME "default")
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
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/antenna/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/aodv/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/applications/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/bridge/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/brite/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/buildings/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/click/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/config-store/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/core/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/csma/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/csma-layout/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/dsdv/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/dsr/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/energy/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/fd-net-device/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/flow-monitor/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/internet/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/internet-apps/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/lr-wpan/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/lte/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/mesh/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/mobility/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/netanim/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/network/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/nix-vector-routing/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/olsr/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/openflow/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/point-to-point/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/point-to-point-layout/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/propagation/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/sixlowpan/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/spectrum/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/stats/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/tap-bridge/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/topology-read/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/traffic-control/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/uan/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/virtual-net-device/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/wifi/cmake_install.cmake")
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/test/src/wimax/cmake_install.cmake")

endif()

