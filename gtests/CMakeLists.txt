
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories( ${PROJECT_SOURCE_DIR}/helicopter )
include_directories( ${PROJECT_SOURCE_DIR}/dsp)
include_directories( ${PROJECT_SOURCE_DIR}/dsp/stk_partial )
include_directories( ${PROJECT_SOURCE_DIR}/dsp/iowahills_partial )

set(HELICOPTER_DIR ${PROJECT_SOURCE_DIR}/helicopter)
set(FILTER_DIR ${PROJECT_SOURCE_DIR}/dsp)
set(IOWA_HILLS_DIR ${PROJECT_SOURCE_DIR}/dsp/iowahills_partial)

set(PThreadLib -pthread)

add_executable(runUnitTests
    testLoadingNoise.cpp
    testCompressorNoise.cpp
    testOneThirdOctaveBand.cpp

    ${HELICOPTER_DIR}/RotationalNoise.cpp
    ${HELICOPTER_DIR}/CompressorNoise.cpp
    ${HELICOPTER_DIR}/SourceNoise.cpp
    ${HELICOPTER_DIR}/BladeElementMomentumTheory.cpp
    ${FILTER_DIR}/OneThirdOctaveBand.cpp
)

target_link_libraries(runUnitTests
    ${PThreadLib}
    ${GTEST_BOTH_LIBRARIES}
)

set_property(TARGET runUnitTests PROPERTY CXX_STANDARD 14)
set_property(TARGET runUnitTests PROPERTY CXX_STANDARD_REQUIRED ON)

add_test(
    NAME runUnitTests
    COMMAND runUnitTests
)
