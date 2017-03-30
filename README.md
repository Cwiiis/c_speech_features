# C Speech Features

This library is a complete port of [python_speech_features](https://github.com/jameslyons/python_speech_features) to C. Currently, only 32-bit float is supported.

## Usage

Clone this repository in your C/C++ project:

```
git clone https://github.com/cwiiis/c_speech_features
```

and add these files to your build:

```
c_speech_features.c
kiss_fft130/kiss_fft.c
kiss_fft130/tools/kiss_fftr.c
```

Refer to [c_speech_features.h](c_speech_features.h) for documentation.
