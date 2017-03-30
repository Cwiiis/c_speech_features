cmake_minimum_required (VERSION 3.6)
project (c_speech_features)

set (SRC c_speech_features.c kiss_fft130/kiss_fft.c kiss_fft130/tools/kiss_fftr.c)

include_directories (kiss_fft130 kiss_fft130/tools)

add_library (c_speech_features SHARED ${SRC})
add_library (c_speech_features_static STATIC ${SRC})
