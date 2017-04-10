cmake_minimum_required (VERSION 3.6)
project (c_speech_features)

include(GNUInstallDirs)

option (ENABLE_DOUBLE "Enable double-precision floats" OFF)
if (ENABLE_DOUBLE)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Dkiss_fft_scalar=double")
endif ()
configure_file ("c_speech_features_config.h.in" "c_speech_features_config.h")

add_library (objlib OBJECT c_speech_features.c kiss_fft130/kiss_fft.c kiss_fft130/tools/kiss_fftr.c)
set_property (TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)

include_directories (kiss_fft130 kiss_fft130/tools)

add_library (c_speech_features SHARED $<TARGET_OBJECTS:objlib>)
add_library (c_speech_features_static STATIC $<TARGET_OBJECTS:objlib>)

install (TARGETS c_speech_features c_speech_features_static DESTINATION ${CMAKE_INSTALL_LIBDIR})
install (FILES c_speech_features.h c_speech_features_config.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
