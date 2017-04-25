#include "c_speech_features.h"
#include "base.h"
#include <stdlib.h>
#include <string.h>

void
mfcc(const short* aSignal, unsigned int aSignalLen, int aSampleRate,
     csf_float aWinLen, csf_float aWinStep,
     int aNCep, int aNFilters, int aNFFT,
     int aLowFreq, int aHighFreq, csf_float aPreemph,
     int aCepLifter, int aAppendEnergy,
     csf_float* aWinFunc,
     csf_float** aMFCC, int* mfcc_d1, int* mfcc_d2)
{
  *mfcc_d1 = csf_mfcc(aSignal, aSignalLen, aSampleRate, aWinLen, aWinStep,
                      aNCep, aNFilters, aNFFT, aLowFreq, aHighFreq, aPreemph,
                      aCepLifter, aAppendEnergy, aWinFunc, aMFCC);
  *mfcc_d2 = aNCep;
}

void
fbank(const short* signal, unsigned int signal_len, int samplerate,
      csf_float winlen, csf_float winstep, int nfilt, int nfft,
      int lowfreq, int highfreq, csf_float preemph,
      csf_float* winfunc,
      csf_float** features, int* features_dim1, int* features_dim2,
      csf_float** energy, int* energy_dim1)
{
  *features_dim1 = csf_fbank(signal, signal_len, samplerate, winlen, winstep,
                             nfilt, nfft, lowfreq, highfreq, preemph, winfunc,
                             features, energy);
  *features_dim2 = nfilt;
  *energy_dim1 = *features_dim1;
}

void
logfbank(const short* signal, unsigned int signal_len, int samplerate,
         csf_float winlen, csf_float winstep, int nfilt, int nfft,
         int lowfreq, int highfreq, csf_float preemph,
         csf_float* winfunc,
         csf_float** features, int* features_dim1, int* features_dim2)
{
  *features_dim1 = csf_logfbank(signal, signal_len, samplerate, winlen,
                                winstep, nfilt, nfft, lowfreq, highfreq,
                                preemph, winfunc, features, 0);
  *features_dim2 = nfilt;
}

void
ssc(const short* signal, unsigned int signal_len, int samplerate,
    csf_float winlen, csf_float winstep, int nfilt, int nfft,
    int lowfreq, int highfreq, csf_float preemph,
    csf_float* winfunc,
    csf_float** features, int* features_dim1, int* features_dim2)
{
  *features_dim1 = csf_ssc(signal, signal_len, samplerate, winlen, winstep,
                           nfilt, nfft, lowfreq, highfreq, preemph,
                           winfunc, features);
  *features_dim2 = nfilt;
}

csf_float
hz2mel(csf_float hz)
{
  return CSF_HZ2MEL(hz);
}

csf_float
mel2hz(csf_float mel)
{
  return CSF_MEL2HZ(mel);
}

void
get_filterbanks(int nfilt, int nfft,
                int samplerate, int lowfreq, int highfreq,
                csf_float** filterbanks,
                int* filterbanks_dim1, int* filterbanks_dim2)
{
  *filterbanks =
    csf_get_filterbanks(nfilt, nfft, samplerate, lowfreq, highfreq);
  *filterbanks_dim1 = nfilt;
  *filterbanks_dim2 = nfft / 2 + 1;
}

void
lifter(csf_float* cepstra, int cepstra_dim1, int cepstra_dim2, int L,
       csf_float** cepstra_out, int* cepstra_out_dim1, int* cepstra_out_dim2)
{
  csf_lifter(cepstra, cepstra_dim1, cepstra_dim2, L);
  size_t cepstra_size = sizeof(csf_float) * cepstra_dim1 * cepstra_dim2;
  *cepstra_out = malloc(cepstra_size);
  *cepstra_out_dim1 = cepstra_dim1;
  *cepstra_out_dim2 = cepstra_dim2;
  memcpy(*cepstra_out, cepstra, cepstra_size);
}

void
delta(csf_float* feat, int feat_dim1, int feat_dim2, int N,
      csf_float** delta, int* delta_dim1, int* delta_dim2)
{
  *delta = csf_delta((const csf_float*)feat, feat_dim1, feat_dim2, N);
  *delta_dim1 = feat_dim1;
  *delta_dim2 = feat_dim2;
}
