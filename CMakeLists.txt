cmake_minimum_required(VERSION 3.16)
project(SAT_NETWORK_SIM)

set(CMAKE_CXX_STANDARD 17)

# =========================
# GLFW (system via pkg-config)
# =========================
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# =========================
# Include directories
# =========================
include_directories(
    include
)

# =========================
# Main executable
# =========================
add_executable(SAT_NETWORK_SIM
    src/main.cpp
    src/glad.c
    src/sim/Satellite/Satellite.cpp
    src/sim/Doppler/Doppler.hpp
    src/sim/Sim.cpp
    src/ui/MainWindow.cpp
    src/util/Spheroid/Spheroid.cpp
)

target_include_directories(SAT_NETWORK_SIM PRIVATE ${GLFW_INCLUDE_DIRS})

target_link_libraries(SAT_NETWORK_SIM
    ${GLFW_LIBRARIES}
    GL
    dl
    pthread
    X11
)

# =========================
# GoogleTest
# =========================
find_package(GTest REQUIRED)

# =========================
# TEST EXECUTABLE
# =========================
add_executable(tests
    tests/satelliteTests.cpp
    tests/dopplerTests.cpp
    src/sim/Satellite/Satellite.cpp
    src/sim/Doppler/Doppler.cpp
    src/sim/Sim.cpp
)

target_include_directories(tests PRIVATE include)

target_link_libraries(tests
    GTest::gtest
    GTest::gtest_main
    pthread
)

# =========================
# Run targets (AFTER executables exist)
# =========================
add_custom_target(run
    COMMAND $<TARGET_FILE:SAT_NETWORK_SIM>
    DEPENDS SAT_NETWORK_SIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(run_tests
    COMMAND $<TARGET_FILE:tests>
    DEPENDS tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)