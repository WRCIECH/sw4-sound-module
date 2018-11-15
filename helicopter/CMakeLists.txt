cmake_minimum_required (VERSION 2.6)
include_directories( ${PROJECT_SOURCE_DIR}/helicopter )
include_directories( ${PROJECT_SOURCE_DIR}/dsp)
include_directories( ${PROJECT_SOURCE_DIR}/dsp/stk_partial )

add_executable(gearbox_noise
gearbox_noise.cpp
GearboxNoise.cpp
GearboxNoise.h
${PROJECT_SOURCE_DIR}/dsp/FilterAdapters.h
${PROJECT_SOURCE_DIR}/dsp/FilterAdapters.cpp

${STK_PARTIAL_DIRECTORY}/Stk.cpp
${STK_PARTIAL_DIRECTORY}/SineWave.cpp
${STK_PARTIAL_DIRECTORY}/RtAudio.cpp
${STK_PARTIAL_DIRECTORY}/RtWvOut.cpp
${STK_PARTIAL_DIRECTORY}/Mutex.cpp
${STK_PARTIAL_DIRECTORY}/Noise.cpp
${STK_PARTIAL_DIRECTORY}/OnePole.cpp
${STK_PARTIAL_DIRECTORY}/OneZero.cpp
${STK_PARTIAL_DIRECTORY}/BlitSaw.cpp
${STK_PARTIAL_DIRECTORY}/BiQuad.cpp
${STK_PARTIAL_DIRECTORY}/Delay.cpp
)

TARGET_LINK_LIBRARIES(gearbox_noise
    ${CMAKE_THREAD_LIBS_INIT}
    ${ALSA_LIBRARY}
    ${SFML_LIBRARY}/libsfml-network-s.a
    ${SFML_LIBRARY}/libsfml-system-s.a
    )
set_property(TARGET gearbox_noise PROPERTY CXX_STANDARD 14)
set_property(TARGET gearbox_noise PROPERTY CXX_STANDARD_REQUIRED ON)


add_executable(rotational_noise
rotational_noise.cpp
SourceNoise.h
SourceNoise.cpp
RotationalNoise.cpp
RotationalNoise.h
BladeElementMomentumTheory.cpp

${PROJECT_SOURCE_DIR}/dsp/FilterAdapters.h
${PROJECT_SOURCE_DIR}/dsp/FilterAdapters.cpp
${STK_PARTIAL_DIRECTORY}/Stk.cpp
${STK_PARTIAL_DIRECTORY}/SineWave.cpp
${STK_PARTIAL_DIRECTORY}/RtAudio.cpp
${STK_PARTIAL_DIRECTORY}/RtWvOut.cpp
${STK_PARTIAL_DIRECTORY}/Mutex.cpp
${STK_PARTIAL_DIRECTORY}/Noise.cpp
${STK_PARTIAL_DIRECTORY}/OnePole.cpp
${STK_PARTIAL_DIRECTORY}/OneZero.cpp
${STK_PARTIAL_DIRECTORY}/BlitSaw.cpp
${STK_PARTIAL_DIRECTORY}/BiQuad.cpp
${STK_PARTIAL_DIRECTORY}/Delay.cpp
)

TARGET_LINK_LIBRARIES(rotational_noise
    ${CMAKE_THREAD_LIBS_INIT}
    ${ALSA_LIBRARY}
    ${SFML_LIBRARY}/libsfml-network-s.a
    ${SFML_LIBRARY}/libsfml-system-s.a
    )
set_property(TARGET rotational_noise PROPERTY CXX_STANDARD 14)
set_property(TARGET rotational_noise PROPERTY CXX_STANDARD_REQUIRED ON)


add_executable(compressor_noise
compressor_noise.cpp
SourceNoise.h
SourceNoise.cpp
CompressorNoise.cpp
CompressorNoise.h

${PROJECT_SOURCE_DIR}/dsp/FilterAdapters.h
${PROJECT_SOURCE_DIR}/dsp/FilterAdapters.cpp
${PROJECT_SOURCE_DIR}/dsp/OneThirdOctaveBand.cpp
${PROJECT_SOURCE_DIR}/dsp/TonalAndBroadbandNoise.cpp

${STK_PARTIAL_DIRECTORY}/Stk.cpp
${STK_PARTIAL_DIRECTORY}/SineWave.cpp
${STK_PARTIAL_DIRECTORY}/RtAudio.cpp
${STK_PARTIAL_DIRECTORY}/RtWvOut.cpp
${STK_PARTIAL_DIRECTORY}/Mutex.cpp
${STK_PARTIAL_DIRECTORY}/Noise.cpp
${STK_PARTIAL_DIRECTORY}/OnePole.cpp
${STK_PARTIAL_DIRECTORY}/OneZero.cpp
${STK_PARTIAL_DIRECTORY}/BlitSaw.cpp
${STK_PARTIAL_DIRECTORY}/BiQuad.cpp
${STK_PARTIAL_DIRECTORY}/Delay.cpp
)

TARGET_LINK_LIBRARIES(compressor_noise
    ${CMAKE_THREAD_LIBS_INIT}
    ${ALSA_LIBRARY}
    ${SFML_LIBRARY}/libsfml-network-s.a
    ${SFML_LIBRARY}/libsfml-system-s.a
    )
set_property(TARGET compressor_noise PROPERTY CXX_STANDARD 14)
set_property(TARGET compressor_noise PROPERTY CXX_STANDARD_REQUIRED ON)


add_executable(helicopter_noise
helicopter_noise.cpp
SourceNoise.h
SourceNoise.cpp
CompressorNoise.cpp
CompressorNoise.h
RotationalNoise.cpp
RotationalNoise.h
BladeElementMomentumTheory.cpp
GearboxNoise.cpp
GearboxNoise.h

${PROJECT_SOURCE_DIR}/dsp/FilterAdapters.h
${PROJECT_SOURCE_DIR}/dsp/FilterAdapters.cpp
${PROJECT_SOURCE_DIR}/dsp/OneThirdOctaveBand.cpp
${PROJECT_SOURCE_DIR}/dsp/TonalAndBroadbandNoise.cpp

${STK_PARTIAL_DIRECTORY}/Stk.cpp
${STK_PARTIAL_DIRECTORY}/SineWave.cpp
${STK_PARTIAL_DIRECTORY}/RtAudio.cpp
${STK_PARTIAL_DIRECTORY}/RtWvOut.cpp
${STK_PARTIAL_DIRECTORY}/Mutex.cpp
${STK_PARTIAL_DIRECTORY}/Noise.cpp
${STK_PARTIAL_DIRECTORY}/OnePole.cpp
${STK_PARTIAL_DIRECTORY}/OneZero.cpp
${STK_PARTIAL_DIRECTORY}/BlitSaw.cpp
${STK_PARTIAL_DIRECTORY}/BiQuad.cpp
${STK_PARTIAL_DIRECTORY}/Delay.cpp
)

TARGET_LINK_LIBRARIES(helicopter_noise
    ${CMAKE_THREAD_LIBS_INIT}
    ${ALSA_LIBRARY}
    ${SFML_LIBRARY}/libsfml-network-s.a
    ${SFML_LIBRARY}/libsfml-system-s.a
    )
set_property(TARGET helicopter_noise PROPERTY CXX_STANDARD 14)
set_property(TARGET helicopter_noise PROPERTY CXX_STANDARD_REQUIRED ON)
