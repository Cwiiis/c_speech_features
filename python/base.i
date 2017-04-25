%module c_speech_features_base

%pythoncode %{
from c_speech_features import c_speech_features_sigproc as sigproc
%}

%import "../c_speech_features_config.h"
%{
#define SWIG_FILE_WITH_INIT
#include "c_speech_features.h"
#include "base.h"
%}

%include "numpy.i"
%init %{
import_array();
%}

%apply (short* IN_ARRAY1, int DIM1) {(const short* signal, unsigned int signal_len)};
%apply (csf_float* IN_ARRAY1) {(csf_float* winfunc)};
%apply (csf_float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(csf_float** mfcc, int* mfcc_dim1, int* mfcc_dim2)};
%apply (csf_float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(csf_float** features, int* features_dim1, int* features_dim2)};
%apply (csf_float** ARGOUTVIEWM_ARRAY1, int* DIM1) {(csf_float** energy, int* energy_dim1)};
%apply (csf_float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(csf_float** filterbanks, int* filterbanks_dim1, int* filterbanks_dim2)};
%apply (csf_float* IN_ARRAY2, int DIM1, int DIM2) {(csf_float* cepstra, int cepstra_dim1, int cepstra_dim2)};
%apply (csf_float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(csf_float** cepstra_out, int* cepstra_out_dim1, int* cepstra_out_dim2)};
%apply (csf_float* IN_ARRAY2, int DIM1, int DIM2) {(csf_float* feat, int feat_dim1, int feat_dim2)};
%apply (csf_float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(csf_float** delta, int* delta_dim1, int* delta_dim2)};

%typemap(default) int samplerate { $1 = 16000; }
%typemap(default) csf_float winlen { $1 = 0.025; }
%typemap(default) csf_float winstep { $1 = 0.01; }
%typemap(default) int numcep { $1 = 13; }
%typemap(default) int nfilt { $1 = 26; }
%typemap(default) int nfft { $1 = 512; }
%typemap(default) int lowfreq { $1 = 0; }
%typemap(default) int highfreq { $1 = 0; }
%typemap(default) csf_float preemph { $1 = 0.97; }
%typemap(default) int ceplifter { $1 = 22; }
%typemap(default) int appendEnergy { $1 = 1; }
%typemap(default) csf_float* winfunc { $1 = NULL; }
%typemap(default) int L { $1 = 22; }

void mfcc(const short* signal,
          unsigned int signal_len,
          int samplerate,
          csf_float winlen,
          csf_float winstep,
          int numcep,
          int nfilt,
          int nfft,
          int lowfreq,
          int highfreq,
          csf_float preemph,
          int ceplifter,
          int appendEnergy,
          csf_float* winfunc,
          csf_float** mfcc,
          int* mfcc_dim1,
          int* mfcc_dim2);

void fbank(const short* signal,
           unsigned int signal_len,
           int samplerate,
           csf_float winlen,
           csf_float winstep,
           int nfilt,
           int nfft,
           int lowfreq,
           int highfreq,
           csf_float preemph,
           csf_float* winfunc,
           csf_float** features,
           int* features_dim1,
           int* features_dim2,
           csf_float** energy,
           int* energy_dim1);

void logfbank(const short* signal,
              unsigned int signal_len,
              int samplerate,
              csf_float winlen,
              csf_float winstep,
              int nfilt,
              int nfft,
              int lowfreq,
              int highfreq,
              csf_float preemph,
              csf_float* winfunc,
              csf_float** features,
              int* features_dim1,
              int* features_dim2);

void ssc(const short* signal,
         unsigned int signal_len,
         int samplerate,
         csf_float winlen,
         csf_float winstep,
         int nfilt,
         int nfft,
         int lowfreq,
         int highfreq,
         csf_float preemph,
         csf_float* winfunc,
         csf_float** features,
         int* features_dim1,
         int* features_dim2);

csf_float hz2mel(csf_float hz);

csf_float mel2hz(csf_float mel);

%typemap(default) int nfilt { $1 = 20; }

void get_filterbanks(int nfilt,
                     int nfft,
                     int samplerate,
                     int lowfreq,
                     int highfreq,
                     csf_float** filterbanks,
                     int* filterbanks_dim1,
                     int* filterbanks_dim2);

void lifter(csf_float* cepstra,
            int cepstra_dim1,
            int cepstra_dim2,
            int L,
            csf_float** cepstra_out,
            int* cepstra_out_dim1,
            int* cepstra_out_dim2);

void delta(csf_float* feat,
           int feat_dim1,
           int feat_dim2,
           int N,
           csf_float** delta,
           int* delta_dim1,
           int* delta_dim2);
