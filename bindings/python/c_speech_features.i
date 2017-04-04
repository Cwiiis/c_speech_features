%module c_speech_features
%{
#define SWIG_FILE_WITH_INIT
#include "../../c_speech_features.h"
#include "helper.h"
%}

%include "numpy.i"
%init %{
import_array();
%}

%apply (short* IN_ARRAY1, int DIM1) {(const short* signal, unsigned int signal_len)};
%apply (float* IN_ARRAY1, int DIM1) {(float* sig, unsigned int sig_len)};
%apply (float* IN_ARRAY1) {(float* winfunc)};
%apply (float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(float** mfcc, int* mfcc_dim1, int* mfcc_dim2)};
%apply (float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(float** features, int* features_dim1, int* features_dim2)};
%apply (float** ARGOUTVIEWM_ARRAY1, int* DIM1) {(float** energy, int* energy_dim1)};
%apply (float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(float** filterbanks, int* filterbanks_dim1, int* filterbanks_dim2)};
%apply (float* IN_ARRAY2, int DIM1, int DIM2) {(float* cepstra, int cepstra_dim1, int cepstra_dim2)};
%apply (float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(float** cepstra_out, int* cepstra_out_dim1, int* cepstra_out_dim2)};
%apply (float* IN_ARRAY2, int DIM1, int DIM2) {(float* feat, int feat_dim1, int feat_dim2)};
%apply (float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(float** delta, int* delta_dim1, int* delta_dim2)};
%apply (float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(float** frames, int* frames_dim1, int* frames_dim2)};
%apply (float* IN_ARRAY2, int DIM1, int DIM2) {(float* frames, int frames_dim1, int frames_dim2)};
%apply (float** ARGOUTVIEWM_ARRAY1, int* DIM1) {(float** signal, int* signal_dim1)};
%apply (float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(float** magspec, int* magspec_dim1, int* magspec_dim2)};
%apply (float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(float** powspec, int* powspec_dim1, int* powspec_dim2)};
%apply (float** ARGOUTVIEWM_ARRAY2, int* DIM1, int* DIM2) {(float** logpowspec, int* logpowspec_dim1, int* logpowspec_dim2)};
%apply (float** ARGOUTVIEWM_ARRAY1, int* DIM1) {(float** preemph, int* preemph_dim1)};

%typemap(default) int samplerate { $1 = 16000; }
%typemap(default) float winlen { $1 = 0.025f; }
%typemap(default) float winstep { $1 = 0.01f; }
%typemap(default) int numcep { $1 = 13; }
%typemap(default) int nfilt { $1 = 26; }
%typemap(default) int nfft { $1 = 512; }
%typemap(default) int lowfreq { $1 = 0; }
%typemap(default) int highfreq { $1 = 0; }
%typemap(default) float preemph { $1 = 0.97f; }
%typemap(default) int ceplifter { $1 = 22; }
%typemap(default) int appendEnergy { $1 = 1; }
%typemap(default) float* winfunc { $1 = NULL; }
%typemap(default) int L { $1 = 22; }
%typemap(default) int norm { $1 = 1; }
%typemap(default) float coeff { $1 = 0.95f; }

void mfcc(const short* signal,
          unsigned int signal_len,
          int samplerate,
          float winlen,
          float winstep,
          int numcep,
          int nfilt,
          int nfft,
          int lowfreq,
          int highfreq,
          float preemph,
          int ceplifter,
          int appendEnergy,
          float* winfunc,
          float** mfcc,
          int* mfcc_dim1,
          int* mfcc_dim2);

void fbank(const short* signal,
           unsigned int signal_len,
           int samplerate,
           float winlen,
           float winstep,
           int nfilt,
           int nfft,
           int lowfreq,
           int highfreq,
           float preemph,
           float* winfunc,
           float** features,
           int* features_dim1,
           int* features_dim2,
           float** energy,
           int* energy_dim1);

void logfbank(const short* signal,
              unsigned int signal_len,
              int samplerate,
              float winlen,
              float winstep,
              int nfilt,
              int nfft,
              int lowfreq,
              int highfreq,
              float preemph,
              float* winfunc,
              float** features,
              int* features_dim1,
              int* features_dim2);

void ssc(const short* signal,
         unsigned int signal_len,
         int samplerate,
         float winlen,
         float winstep,
         int nfilt,
         int nfft,
         int lowfreq,
         int highfreq,
         float preemph,
         float* winfunc,
         float** features,
         int* features_dim1,
         int* features_dim2);

float hz2mel(float hz);

float mel2hz(float mel);

%typemap(default) int nfilt { $1 = 20; }

void get_filterbanks(int nfilt,
                     int nfft,
                     int samplerate,
                     int lowfreq,
                     int highfreq,
                     float** filterbanks,
                     int* filterbanks_dim1,
                     int* filterbanks_dim2);

void lifter(float* cepstra,
            int cepstra_dim1,
            int cepstra_dim2,
            int L,
            float** cepstra_out,
            int* cepstra_out_dim1,
            int* cepstra_out_dim2);

void delta(float* feat,
           int feat_dim1,
           int feat_dim2,
           int N,
           float** delta,
           int* delta_dim1,
           int* delta_dim2);

// Sigproc

void framesig(float* sig,
              unsigned int sig_len,
              int frame_len,
              int frame_step,
              float* winfunc,
              float** frames,
              int* frames_dim1,
              int* frames_dim2);

void deframesig(float* frames,
                int frames_dim1,
                int frames_dim2,
                int siglen,
                int frame_len,
                int frame_step,
                float* winfunc,
                float** signal,
                int* signal_dim1);

void magspec(float* frames,
             int frames_dim1,
             int frames_dim2,
             int NFFT,
             float** magspec,
             int* magspec_dim1,
             int* magspec_dim2);

void powspec(float* frames,
             int frames_dim1,
             int frames_dim2,
             int NFFT,
             float** powspec,
             int* powspec_dim1,
             int* powspec_dim2);

void logpowspec(float* frames,
                int frames_dim1,
                int frames_dim2,
                int NFFT,
                int norm,
                float** logpowspec,
                int* logpowspec_dim1,
                int* logpowspec_dim2);

void preemphasis(const short* signal,
                 unsigned int signal_len,
                 float coeff,
                 float** preemph,
                 int* preemph_dim1);
