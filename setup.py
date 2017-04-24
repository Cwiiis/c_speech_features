#! /usr/bin/env python

from setuptools import setup, find_packages, Extension
from setuptools.command.build_ext import build_ext
from distutils.command.build import build

import os
import numpy
import subprocess

try:
    numpy_include = numpy.get_include()
except AttributeError:
    numpy_include = numpy.get_numpy_include()

class BuildExtFirst(build):
    sub_commands = [('build_ext', build.has_ext_modules),
                    ('build_py', build.has_pure_modules),
                    ('build_clib', build.has_c_libraries),
                    ('build_scripts', build.has_scripts)]

class CmakeBuild(build_ext):
    def run(self):
        skip = os.environ.get('SKIP_BUILD')
        if skip == None or skip == '0':
            path = os.path.dirname(os.path.realpath(__file__))
            subprocess.call(['cmake', '-DCMAKE_C_FLAGS=-O3', '-DENABLE_DOUBLE=OFF'], cwd=path)
            subprocess.call(['make'], cwd=path)
        build_ext.run(self)

c_speech_features = Extension('_c_speech_features',
        ['python/c_speech_features.i', 'python/helper.c'],
        include_dirs = [numpy_include],
        libraries = ['c_speech_features_static'])

setup(name = 'c_speech_features',
      description = 'A C re-implementation of python_speech_features',
      author = 'Chris Lord',
      author_email='chrislord.net@gmail.com',
      version = '0.4.6',
      package_dir = {'': 'python'},
      packages = [ '' ],
      cmdclass = { 'build': BuildExtFirst,
                   'build_ext': CmakeBuild },
      license = 'MIT',
      url = 'https://gitlab.com/Cwiiis/c_speech_features',
      ext_modules = [c_speech_features])
