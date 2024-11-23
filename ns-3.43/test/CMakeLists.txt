set(SOURCES
    tcp-davis-test.cc
)

add_executable(run-tests ${SOURCES})
target_link_libraries(run-tests ns3-core ns3-internet)


# Include NS-3 source directories for required headers
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core/model
    ${CMAKE_SOURCE_DIR}/src/internet/model
)

# Register the test executable with CTest
add_test(NAME TcpDavisTest COMMAND run-tests)
