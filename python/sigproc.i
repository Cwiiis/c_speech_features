%module c_speech_features_sigproc
%import "../c_speech_features_config.h"
%{
#define SWIG_FILE_WITH_INIT
#include "c_speech_features.h"
#include "sigproc.h"
%}

%include "numpy.i"
%init %{
import_array();
%}

%apply (short* IN_ARRAY1, int DIM1) {(const short* signal, unsigned int signal_len)};
%apply (csf_float* IN_ARRAY1, int DIM1) {(csf_float* sig, unsigned int sig_len)};
%apply (csf_float* IN_ARRAY1) {(csf_float* winfunc)};
%apply (csf_float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(csf_float** frames, int* frames_dim1, int* frames_dim2)};
%apply (csf_float* IN_ARRAY2, int DIM1, int DIM2) {(csf_float* frames, int frames_dim1, int frames_dim2)};
%apply (csf_float** ARGOUTVIEWM_ARRAY1, int* DIM1) {(csf_float** signal, int* signal_dim1)};
%apply (csf_float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(csf_float** magspec, int* magspec_dim1, int* magspec_dim2)};
%apply (csf_float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(csf_float** powspec, int* powspec_dim1, int* powspec_dim2)};
%apply (csf_float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(csf_float** logpowspec, int* logpowspec_dim1, int* logpowspec_dim2)};
%apply (csf_float** ARGOUTVIEWM_ARRAY1, int* DIM1) {(csf_float** preemph, int* preemph_dim1)};

%typemap(default) csf_float* winfunc { $1 = NULL; }
%typemap(default) int norm { $1 = 1; }
%typemap(default) csf_float coeff { $1 = 0.95; }

%include "sigproc.h"
