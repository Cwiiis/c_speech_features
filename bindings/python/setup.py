#! /usr/bin/env python

from distutils.core import *
from distutils import sysconfig

import os
import numpy

try:
    numpy_include = numpy.get_include()
except AttributeError:
    numpy_include = numpy.get_numpy_include()

_c_speech_features = Extension('_c_speech_features',
        ['c_speech_features.i', 'helper.c'],
        include_dirs = [numpy_include],
        libraries = ['c_speech_features']
        )

setup(name = 'C Speech Features',
      description = 'A C re-implementation of python_speech_features',
      author = 'Chris Lord',
      version = '1.0',
      ext_modules = [_c_speech_features]
      )
