# Install script for directory: /home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network

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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-network-debug.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-network-debug.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-network-debug.so"
         RPATH "/usr/local/lib:$ORIGIN/:$ORIGIN/../lib:/usr/local/lib64:$ORIGIN/:$ORIGIN/../lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/lib/libns3.43-network-debug.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-network-debug.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-network-debug.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-network-debug.so"
         OLD_RPATH "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/lib::::::::::::::::::::::::::::"
         NEW_RPATH "/usr/local/lib:$ORIGIN/:$ORIGIN/../lib:/usr/local/lib64:$ORIGIN/:$ORIGIN/../lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.43-network-debug.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ns3" TYPE FILE FILES
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/helper/application-container.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/helper/application-helper.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/helper/delay-jitter-estimation.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/helper/net-device-container.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/helper/node-container.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/helper/packet-socket-helper.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/helper/simple-net-device-helper.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/helper/trace-helper.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/address.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/application.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/buffer.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/byte-tag-list.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/channel-list.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/channel.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/chunk.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/header.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/net-device.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/nix-vector.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/node-list.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/node.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/packet-metadata.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/packet-tag-list.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/packet.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/socket-factory.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/socket.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/tag-buffer.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/tag.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/model/trailer.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/test/header-serialization-test.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/address-utils.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/bit-deserializer.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/bit-serializer.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/crc32.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/data-rate.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/drop-tail-queue.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/dynamic-queue-limits.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/error-channel.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/error-model.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/ethernet-header.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/ethernet-trailer.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/flow-id-tag.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/generic-phy.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/inet-socket-address.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/inet6-socket-address.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/ipv4-address.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/ipv6-address.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/llc-snap-header.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/lollipop-counter.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/mac16-address.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/mac48-address.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/mac64-address.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/mac8-address.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/net-device-queue-interface.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/output-stream-wrapper.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/packet-burst.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/packet-data-calculators.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/packet-probe.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/packet-socket-address.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/packet-socket-client.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/packet-socket-factory.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/packet-socket-server.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/packet-socket.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/packetbb.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/pcap-file-wrapper.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/pcap-file.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/pcap-test.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/queue-fwd.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/queue-item.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/queue-limits.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/queue-size.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/queue.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/radiotap-header.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/sequence-number.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/simple-channel.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/simple-net-device.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/sll-header.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/network/utils/timestamp-tag.h"
    "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/build/include/ns3/network-module.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/cmake-cache/src/network/examples/cmake_install.cmake")

endif()

