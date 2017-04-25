#include "c_speech_features.h"
#include "sigproc.h"
#include <stdlib.h>
#include <string.h>

void
framesig(csf_float* sig, unsigned int sig_len,
         int frame_len, int frame_step, csf_float* winfunc,
         csf_float** frames, int* frames_dim1, int* frames_dim2)
{
  *frames_dim1 = csf_framesig((const csf_float*)sig, sig_len, frame_len,
                              frame_len, frame_step, winfunc, frames);
  *frames_dim2 = frame_len;
}

void
deframesig(csf_float* frames, int frames_dim1, int frames_dim2,
           int siglen, int frame_len, int frame_step, csf_float* winfunc,
           csf_float** signal, int* signal_dim1)
{
  *signal_dim1 = csf_deframesig(frames, frames_dim1, siglen,
                                frame_len, frame_step, winfunc, signal);
}

static csf_float*
resize_2d_array_width(csf_float* array, int d1, int d2, int t2)
{
    int i, idx, idx2;
    int size = d2 < t2 ? d2 : t2;
    csf_float* array_copy = calloc(sizeof(csf_float), d1 * t2);
    for (i = 0, idx = 0, idx2 = 0; i < d1; i++, idx += t2, idx2 += d2) {
      memcpy(array_copy + idx, array + idx2, size * sizeof(csf_float));
    }
    return array_copy;
}

void
magspec(csf_float* frames, int frames_dim1, int frames_dim2,
        int NFFT,
        csf_float** magspec, int* magspec_dim1, int* magspec_dim2)
{
  if (frames_dim2 != NFFT) {
    frames = resize_2d_array_width(frames, frames_dim1, frames_dim2, NFFT);
  }

  *magspec = csf_magspec(frames, frames_dim1, NFFT);
  *magspec_dim1 = frames_dim1;
  *magspec_dim2 = NFFT / 2 + 1;

  if (frames_dim2 != NFFT) {
    free (frames);
  }
}

void
powspec(csf_float* frames, int frames_dim1, int frames_dim2,
        int NFFT,
        csf_float** powspec, int* powspec_dim1, int* powspec_dim2)
{
  if (frames_dim2 != NFFT) {
    frames = resize_2d_array_width(frames, frames_dim1, frames_dim2, NFFT);
  }

  *powspec = csf_powspec(frames, frames_dim1, NFFT);
  *powspec_dim1 = frames_dim1;
  *powspec_dim2 = NFFT / 2 + 1;

  if (frames_dim2 != NFFT) {
    free (frames);
  }
}

void
logpowspec(csf_float* frames, int frames_dim1, int frames_dim2,
           int NFFT, int norm,
           csf_float** logpowspec, int* logpowspec_dim1, int* logpowspec_dim2)
{
  if (frames_dim2 != NFFT) {
    frames = resize_2d_array_width(frames, frames_dim1, frames_dim2, NFFT);
  }

  *logpowspec = csf_logpowspec(frames, frames_dim1, NFFT, norm);
  *logpowspec_dim1 = frames_dim1;
  *logpowspec_dim2 = NFFT / 2 + 1;

  if (frames_dim2 != NFFT) {
    free (frames);
  }
}

void
preemphasis(const short* signal, unsigned int signal_len,
            csf_float coeff,
            csf_float** preemph, int* preemph_dim1)
{
  *preemph = csf_preemphasis(signal, signal_len, coeff);
  *preemph_dim1 = signal_len;
}
