cmake_minimum_required (VERSION 3.6)
project (c_speech_features)

include(GNUInstallDirs)

add_library (objlib OBJECT c_speech_features.c kiss_fft130/kiss_fft.c kiss_fft130/tools/kiss_fftr.c)
set_property (TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)

include_directories (kiss_fft130 kiss_fft130/tools)

add_library (c_speech_features SHARED $<TARGET_OBJECTS:objlib>)
add_library (c_speech_features_static STATIC $<TARGET_OBJECTS:objlib>)

install (TARGETS c_speech_features c_speech_features_static DESTINATION ${CMAKE_INSTALL_LIBDIR})
install (FILES c_speech_features.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
