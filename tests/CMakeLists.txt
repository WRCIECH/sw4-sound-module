cmake_minimum_required (VERSION 2.6)


add_executable(amplitude_modulation
amplitude_modulation.cpp
${STK_PARTIAL_DIRECTORY}/Stk.cpp
${STK_PARTIAL_DIRECTORY}/SineWave.cpp
${STK_PARTIAL_DIRECTORY}/Noise.cpp
${STK_PARTIAL_DIRECTORY}/RtAudio.cpp
${STK_PARTIAL_DIRECTORY}/RtWvOut.cpp
${STK_PARTIAL_DIRECTORY}/Mutex.cpp
)

TARGET_LINK_LIBRARIES(amplitude_modulation
    ${CMAKE_THREAD_LIBS_INIT}
    ${ALSA_LIBRARY}
    ${SFML_LIBRARY}/libsfml-network-s.a
    ${SFML_LIBRARY}/libsfml-system-s.a
    )

set_property(TARGET amplitude_modulation PROPERTY CXX_STANDARD 14)
set_property(TARGET amplitude_modulation PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(filter_tester
filter_tester.cpp
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

TARGET_LINK_LIBRARIES(filter_tester
    ${CMAKE_THREAD_LIBS_INIT}
    ${ALSA_LIBRARY}
    ${SFML_LIBRARY}/libsfml-network-s.a
    ${SFML_LIBRARY}/libsfml-system-s.a
    )
set_property(TARGET filter_tester PROPERTY CXX_STANDARD 14)
set_property(TARGET filter_tester PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(read_wav_file
read_wav_file.cpp
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
${STK_PARTIAL_DIRECTORY}/Fir.cpp
${STK_PARTIAL_DIRECTORY}/FileWrite.cpp
${STK_PARTIAL_DIRECTORY}/FileLoop.cpp
${STK_PARTIAL_DIRECTORY}/FileRead.cpp
${STK_PARTIAL_DIRECTORY}/FileWvIn.cpp
${STK_PARTIAL_DIRECTORY}/FileWvOut.cpp
)

TARGET_LINK_LIBRARIES(read_wav_file
    ${CMAKE_THREAD_LIBS_INIT}
    ${ALSA_LIBRARY}
    ${SFML_LIBRARY}/libsfml-network-s.a
    ${SFML_LIBRARY}/libsfml-system-s.a
    )
set_property(TARGET read_wav_file PROPERTY CXX_STANDARD 14)
set_property(TARGET read_wav_file PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(fft_decompositions
fft_decompositions.cpp
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
${STK_PARTIAL_DIRECTORY}/Fir.cpp
)

TARGET_LINK_LIBRARIES(fft_decompositions
    ${CMAKE_THREAD_LIBS_INIT}
    ${ALSA_LIBRARY}
    ${SFML_LIBRARY}/libsfml-network-s.a
    ${SFML_LIBRARY}/libsfml-system-s.a
    fftw3
    )
set_property(TARGET fft_decompositions PROPERTY CXX_STANDARD 14)
set_property(TARGET fft_decompositions PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(create_filter_data
create_filter_data.cpp
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

TARGET_LINK_LIBRARIES(create_filter_data
    ${CMAKE_THREAD_LIBS_INIT}
    ${ALSA_LIBRARY}
    ${SFML_LIBRARY}/libsfml-network-s.a
    ${SFML_LIBRARY}/libsfml-system-s.a
    )
set_property(TARGET create_filter_data PROPERTY CXX_STANDARD 14)
set_property(TARGET create_filter_data PROPERTY CXX_STANDARD_REQUIRED ON)


add_executable(biquad_filter
biquad_filter.cpp
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

TARGET_LINK_LIBRARIES(biquad_filter
    ${CMAKE_THREAD_LIBS_INIT}
    ${ALSA_LIBRARY}
    )
set_property(TARGET biquad_filter PROPERTY CXX_STANDARD 14)
set_property(TARGET biquad_filter PROPERTY CXX_STANDARD_REQUIRED ON)


