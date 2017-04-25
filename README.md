# C Speech Features

This library is a complete port of [python_speech_features](https://github.com/jameslyons/python_speech_features) to C.

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

Alternatively, you can build shared and static libraries to use with your project instead of importing the files directly. Using cmake, from within a check-out:

```
cmake -DCMAKE_C_FLAGS="-O2" -DCMAKE_INSTALL_PREFIX="/usr/local" -DENABLE_DOUBLE=OFF
make
```

This will result in libc_speech_features.so and libc_speech_features_static.a being built (or platform equivalents), which you can link in your project. An install target is also provided, allowing system-wide use of the library, but this is not recommended.

Refer to [c_speech_features.h](c_speech_features.h) for documentation.

## Bindings

### Python

Building python bindings requires [SWIG](http://www.swig.org/) and [numpy](http://www.numpy.org/). Run:

```
python setup.py install
```

This will build and install the statically linked c_speech_features module, which can then be used in any python script. Refer to [python/test/test.py](python/test/test.py) to see examples of its use. For the most part, it is a drop-in replacement for python_speech_features.

### Differences to python_speech_features

* c_speech_features only supports one datatype, which is defined at compile-time. Currently, this can be either 32-bit (float), or 64-bit (double). python_speech_features operates in 64-bit by default.
* The `winfunc` parameter is an array instead of a function, and is expected to be as wide as necessary depending on context.

### Uses

It is not recommended to replace python_speech_features with c_speech_features in a Python context. python_speech_features is safer and will output better error messages when fed with incorrect parameters. c_speech_features is most likely to crash in such situations. On the other hand, this module can be useful to debug issues when using c_speech_features in more appropriate contexts, or if you have very specific needs. c_speech_features is likely to perform faster when compiled with optimisation than python_speech_features. In 64-bit, the gains are minimal, except for particular functions, where as in 32-bit the gains can be substantial (at the cost of precision).
