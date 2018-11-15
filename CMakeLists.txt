cmake_minimum_required (VERSION 2.6)
project (sw4-sound-module)

# Dołączanie biblioteki wątków
find_package (Threads)

# Dołączanie biblioteki alsa
find_path(ALSA_INCLUDE_DIR NAMES alsa/asoundlib.h
          DOC "The ALSA (asound) include directory"
)
if(NOT ALSA_INCLUDE_DIR)
  message(FATAL_ERROR "alsa include dir not found")
endif()

find_library(ALSA_LIBRARY NAMES asound
          DOC "The ALSA (asound) library"
)
if(NOT ALSA_LIBRARY)
  message(FATAL_ERROR "alsa library not found")
endif()

#Dołączenie biblioteki do szybkiej transformaty Fouriera
if (FFTW_INCLUDES)
  # Already in cache, be silent
  set (FFTW_FIND_QUIETLY TRUE)
endif (FFTW_INCLUDES)
find_path (FFTW_INCLUDES fftw.h)
find_library (FFTW_LIBRARIES NAMES fftw)


set(MY_COMPILE_FLAGS "-lasound")

add_definitions(${MY_COMPILE_FLAGS})

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(STK_PARTIAL_DIRECTORY ${PROJECT_SOURCE_DIR}/dsp/stk_partial)
set(SFML_INCLUDE_LIBRARY /home/wojciech/libraries/SFML-2.5.0/include)
set(SFML_LIBRARY /home/wojciech/libraries/SFML-2.5.0/lib)
set(EIGEN_INCLUDE_LIBRARY /home/wojciech/libraries/eigen)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/dsp
    ${ALSA_INCLUDE_DIR}
    ${STK_PARTIAL_DIRECTORY}
    ${SFML_INCLUDE_LIBRARY}
    ${EIGEN_INCLUDE_LIBRARY}
    )

add_subdirectory(tests)
add_subdirectory(gtests)
add_subdirectory(helicopter)
