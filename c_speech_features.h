
/**
 * Calculate filterbank features. Provides e.g. fbank and mfcc features for use
 * in ASR applications.
 *
 * Derived from python_speech_features, by James Lyons.
 * Port by Chris Lord.
 */

#ifndef __C_SPEECH_FEATURES_H__
#define __C_SPEECH_FEATURES_H__

#include <math.h>

#define CSF_HZ2MEL(x) (2595 * log10f(1+(x)/700.0f))
#define CSF_MEL2HZ(x) (700 * (powf(10.0f, (x)/2595.0f) - 1))

#define CSF_2D_INDEX(w,x,y) (((y)*(w))+(x))
#define CSF_2D_REF(m,w,x,y) ((m)[CSF_2D_INDEX(w,x,y)])

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Compute MFCC features from an audio signal.
 *
 * @param aSignal The audio signal from which to compute features.
 * @param aSignalLen The length of the audio signal array.
 * @param aSampleRate The sample-rate of the signal.
 * @param aWinLen The length of the analysis window in seconds. (e.g. 0.025)
 * @param aWinStep The step between successive windows in seconds. (e.g. 0.01)
 * @param aNCep The number of cepstrum to return. (e.g. 13)
 * @param aNFilters The number of filters in the filterbank. (e.g. 26)
 * @param aNFFT The FFT size. (e.g. 512)
 * @param aLowFreq The lowest band edge of mel filters, in hz. (e.g. 0)
 * @param aHighFreq The highest band edge of mel filters, in hz. Must not be
 *                  higher than @p aSampleRate / 2. If this is lower or equal
 *                  to @p aLowFreq, it will be treated as @p aSampleRate / 2.
 * @param aPreemph Preemphasis filter coefficient. 0 is no filter. (e.g. 0.97)
 * @param aCepLifter The lifting coefficient to use. 0 disables lifting.
 *                   (e.g. 22)
 * @param aAppendEnergy If this is true, the zeroth cepstral coefficient is
 *                      replaced with the log of the total frame energy.
 * @param aWinFunc An array of size @p aFrameLen, or @c NULL to be used as an
 *                 analysis window to apply to each frame.
 * @param[out] aMFCC An array containing features, of shape
 *                   (frames, @p aNCep). The user is responsible for freeing
 *                   the array.
 *
 * @return The number of frames.
 */
int csf_mfcc(const short* aSignal,
             unsigned int aSignalLen,
             int aSampleRate,
             float aWinLen,
             float aWinStep,
             int aNCep,
             int aNFilters,
             int aNFFT,
             int aLowFreq,
             int aHighFreq,
             float aPreemph,
             int aCepLifter,
             int aAppendEnergy,
             float* aWinFunc,
             float** aMFCC);

/**
 * @brief Compute Mel-filterbank energy features from an audio signal.
 *
 * Compute Mel-filterbank energy features from an audio signal.
 *
 * @param aSignal The audio signal from which to compute features.
 * @param aSignalLen The length of the audio signal array.
 * @param aSampleRate The sample-rate of the signal.
 * @param aWinLen The length of the analysis window in seconds. (e.g. 0.025)
 * @param aWinStep The step between successive windows in seconds. (e.g. 0.01)
 * @param aNFilters The number of filters in the filterbank. (e.g. 26)
 * @param aNFFT The FFT size. (e.g. 512)
 * @param aLowFreq The lowest band edge of mel filters, in hz. (e.g. 0)
 * @param aHighFreq The highest band edge of mel filters, in hz. Must not be
 *                  higher than @p aSampleRate / 2. If this is lower or equal
 *                  to @p aLowFreq, it will be treated as @p aSampleRate / 2.
 * @param aPreemph Preemphasis filter coefficient. 0 is no filter. (e.g. 0.97)
 * @param aWinFunc An array of size @p aFrameLen, or @c NULL to be used as an
 *                 analysis window to apply to each frame.
 * @param[out] aFeatures A 2D array containing features, of shape
 *                       (frames, @p aNFilters). The user is responsible for
 *                       freeing the array.
 * @param[out] aEnergy An array containing energies, of shape (frames), or
 *                     @c NULL. The user is responsible for freeing the array.
 *
 * @return The number of frames.
 */
int csf_fbank(const short* aSignal,
              unsigned int aSignalLen,
              int aSampleRate,
              float aWinLen,
              float aWinStep,
              int aNFilters,
              int aNFFT,
              int aLowFreq,
              int aHighFreq,
              float aPreemph,
              float* aWinFunc,
              float** aFeatures,
              float** aEnergy);

/**
 * @brief Compute log Mel-filterbank energy features from an audio signal.
 *
 * Compute log Mel-filterbank energy features from an audio signal.
 *
 * @param aSignal The audio signal from which to compute features.
 * @param aSignalLen The length of the audio signal array.
 * @param aSampleRate The sample-rate of the signal.
 * @param aWinLen The length of the analysis window in seconds. (e.g. 0.025)
 * @param aWinStep The step between successive windows in seconds. (e.g. 0.01)
 * @param aNFilters The number of filters in the filterbank. (e.g. 26)
 * @param aNFFT The FFT size. (e.g. 512)
 * @param aLowFreq The lowest band edge of mel filters, in hz. (e.g. 0)
 * @param aHighFreq The highest band edge of mel filters, in hz. Must not be
 *                  higher than @p aSampleRate / 2. If this is lower or equal
 *                  to @p aLowFreq, it will be treated as @p aSampleRate / 2.
 * @param aPreemph Preemphasis filter coefficient. 0 is no filter. (e.g. 0.97)
 * @param aWinFunc An array of size @p aFrameLen, or @c NULL to be used as an
 *                 analysis window to apply to each frame.
 * @param[out] aFeatures A 2D array containing features, of shape
 *                       (frames, @p aNFilters). The user is responsible for
 *                       freeing the array.
 * @param[out] aEnergy An array containing energies, of shape (frames). The
 *                     user is responsible for freeing the array.
 *
 * @return The number of frames.
 */
int csf_logfbank(const short* aSignal,
                 unsigned int aSignalLen,
                 int aSampleRate,
                 float aWinLen,
                 float aWinStep,
                 int aNFilters,
                 int aNFFT,
                 int aLowFreq,
                 int aHighFreq,
                 float aPreemph,
                 float* aWinFunc,
                 float** aFeatures,
                 float** aEnergy);

/**
 * @brief Compute Spectral Sub-band Centroid features from an audio signal.
 *
 * Compute Spectral Sub-band Centroid features from an audio signal.
 *
 * @param aSignal The audio signal from which to compute features.
 * @param aSignalLen The length of the audio signal array.
 * @param aSampleRate The sample-rate of the signal.
 * @param aWinLen The length of the analysis window in seconds. (e.g. 0.025)
 * @param aWinStep The step between successive windows in seconds. (e.g. 0.01)
 * @param aNFilters The number of filters in the filterbank. (e.g. 26)
 * @param aNFFT The FFT size. (e.g. 512)
 * @param aLowFreq The lowest band edge of mel filters, in hz. (e.g. 0)
 * @param aHighFreq The highest band edge of mel filters, in hz. Must not be
 *                  higher than @p aSampleRate / 2. If this is lower or equal
 *                  to @p aLowFreq, it will be treated as @p aSampleRate / 2.
 * @param aPreemph Preemphasis filter coefficient. 0 is no filter. (e.g. 0.97)
 * @param aWinFunc An array of size @p aFrameLen, or @c NULL to be used as an
 *                 analysis window to apply to each frame.
 * @param[out] aFeatures A 2D array containing features, of shape
 *                       (frames, @p aNFilters). The user is responsible for
 *                       freeing the array.
 */
int csf_ssc(const short* aSignal,
            unsigned int aSignalLen,
            int aSampleRate,
            float aWinLen,
            float aWinStep,
            int aNFilters,
            int aNFFT,
            int aLowFreq,
            int aHighFreq,
            float aPreemph,
            float* aWinFunc,
            float** aFeatures);

/**
 * @brief Convert a value in Hertz to Mels
 *
 * Convert a value in Hertz to Mels
 *
 * @param aHz A value in Hz.
 *
 * @return A value in Mels.
 */
float csf_hz2mel(float aHz);

/**
 * @brief Convert a value in Mels to Hertz
 *
 * Convert a value in Mels to Hertz
 *
 * @param aMel A value in Mels.
 *
 * @return A value in Hz.
 */
float csf_mel2hz(float aMel);

/**
 * @brief Compute a Mel-filterbank.
 *
 * Compute a Mel-filterbank. The filters are stored in the rows, the columns
 * correspond to fft bins. The filters are returned as an array of size
 * @p aNFilters * (@p aNFFT / 2 + 1).
 *
 * @param aNFilters The number of filters in the filterbank. (e.g. 20)
 * @param aNFFT The FFT size. (e.g. 512)
 * @param aSampleRate The sample-rate of the signal being worked with. Affects
 *                    mel spacing.
 * @param aLowFreq The lowest band edge of mel filters, in hz. (e.g. 0)
 * @param aHighFreq The highest band edge of mel filters, in hz. Must not be
 *                  higher than @p aSampleRate / 2. If this is lower or equal
 *                  to @p aLowFreq, it will be treated as @p aSampleRate / 2.
 *
 * @return A 2D array of shape (@p aNFilters, @p aNFFT / 2 + 1). The user is
 *         responsible for freeing the array.
 */
float*  csf_get_filterbanks(int aNFilters,
                            int aNFFT,
                            int aSampleRate,
                            int aLowFreq,
                            int aHighFreq);

/**
 * @brief Apply a cepstral lifter on a matrix of cepstra.
 *
 * Apply a cepstral lifter on a matrix of cepstra. This has the effect of
 * increasing the magnitude of high-frequency DCT coefficients.
 *
 * @param aCepstra The 2D array matrix of mel-cepstra.
 * @param aNFrames The number of frames.
 * @param aNCep The number of cepstra per frame.
 * @param aCepLifter The lifting coefficient to use. 0 disables lifting.
 *                   (e.g. 22)
 */
void csf_lifter(float* aCepstra,
                int aNFrames,
                int aNCep,
                int aCepLifter);

/**
 * @brief Compute delta features from a feature vector sequence.
 *
 * Compute delta features from a feature vector sequence.
 *
 * @param aFeatures A 2D array of shape (@p aNFeatures, @p aNFrames). Each row
 *                  holds one feature vector.
 * @param aNFrames The number of frames in @p aFeatures.
 * @param aNFrameLen The length of each frame in @p aFeatures.
 * @param @aN For each frame, calculate delta features based on preceding and
 *            following N frames. Must be 1 or larger.
 *
 * @return A 2D array of shape (@p aNFeatures, @p aNFrames) containing delta
 *         features. Each row contains holds 1 delta feature vector. The user
 *         is responsible for freeing the array.
 */
float* csf_delta(const float* aFeatures,
                 int aNFrames,
                 int aNFrameLen,
                 int aN);

/**
 * @brief Perform preemphasis on an input signal.
 *
 * Perform preemphasis on an input signal.
 *
 * @param aSignal The signal to filter.
 * @param aSignalLen The length of the signal array.
 * @param aCoeff The preemphasis coefficient. 0 is no filter. (e.g. 0.95)
 *
 * @return The filtered signal. The user is responsible for freeing this array.
 */
float* csf_preemphasis(const short* aSignal,
                       unsigned int aSignalLen,
                       float aCoeff);

/**
 * @brief Frame a signal into overlapping frames.
 *
 * Frame a signal into overlapping frames.
 *
 * @param aSignal The signal to frame.
 * @param aSignalLen The length of the signal array.
 * @param aFrameLen The length of each frame in samples.
 * @param aPaddedFrameLen If greater than @p aFrameLen, @p aPaddedFrameLen -
 *                        @p aFrameLen zeros will be appended to each frame.
 * @param aFrameStep The number of samples after the start of the previous frame
 *                   that the next frame should begin.
 * @param aWinFunc An array of size @p aFrameLen, or @c NULL to be used as an
 *                 analysis window to apply to each frame.
 * @param[out] aFrames A 2D array of frames, of shape
 *                     (@c frames, @p aPaddedFrameLen).
 *                     The user is responsible for freeing the array.
 *
 * @return The number of frames.
 */
int csf_framesig(const float* aSignal,
                 unsigned int aSignalLen,
                 int aFrameLen,
                 int aPaddedFrameLen,
                 int aFrameStep,
                 float* aWinFunc,
                 float** aFrames);

/**
 * @brief Perform overlap-add procedure to undo the action of csf_framesig().
 *
 * Perform overlap-add procedure to undo the action of csf_framesig().
 *
 * @param aFrames The 2D array of frames.
 * @param aNFrames The number of frames in @p aFrames.
 * @param aSigLen The length of the desired signal, or 0 if unknown.
 * @param aFrameLen The length of each frame in samples.
 * @param aFrameStep The number of samples after the start of the previous frame
 *                   that the next frame begins
 * @param aWinFunc An array of size @p aFrameLen, or @c NULL to be used as an
 *                 analysis window to apply to each frame.
 * @param[out] aSignal An array of samples. The length will be @p aSigLen if
 *                     specified. The user is responsible for freeing
 *                     this array.
 *
 * @return Returns the length of @p aSignal.
 */
int csf_deframesig(const float* aFrames,
                   int aNFrames,
                   int aSigLen,
                   int aFrameLen,
                   int aFrameStep,
                   float* aWinFunc,
                   float** aSignal);

/**
 * @brief Compute the magnitude spectrum of frames.
 *
 * Compute the magnitude spectrum of each frame in frames.
 *
 * @param aFrames The 2D array of frames, of shape (@p aNFrames, @p aNFFT).
 * @param aNFrames The number of frames.
 * @param aNFFT The FFT length to use.
 *
 * @return A 2D array containing the magnitude spectrum of the
 *         corresponding frame, of shape (@p aNFrames, @p aNFFT / 2 + 1). The
 *         user is responsible for freeing the array.
 */
float* csf_magspec(const float* aFrames,
                   int aNFrames,
                   int aNFFT);

/**
 * @brief Compute the power spectrum of frames.
 *
 * Compute the power spectrum of each frame in frames.
 *
 * @param aFrames The 2D array of frames, of shape (@p aNFrames, @p aNFFT).
 * @param aNFrames The number of frames.
 * @param aNFFT The FFT length to use.
 *
 * @return A 2D array containing the power spectrum of the
 *         corresponding frame, of shape (@p aNFrames, @p aNFFT / 2 + 1).
 *         The user is responsible for freeing the array.
 */
float* csf_powspec(const float* aFrames,
                   int aNFrames,
                   int aNFFT);

/**
 * @brief Compute the log power spectrum of frames.
 *
 * Compute the log power spectrum of each frame in frames.
 *
 * @param aFrames The 2D array of frames, of shape (@p aNFrames, @p aNFFT).
 * @param aNFrames The number of frames.
 * @param aNFFT The FFT length to use.
 * @param aNorm If not zero, the log power spectrum is normalised so that the
 *              maximum value across all frames is 0.
 *
 * @return A 2D array containing the log power spectrum of the
 *         corresponding frame, of shape (@p aNFrames, @p aNFFT / 2 + 1).
 *         The user is responsible for freeing the array.
 */
float* csf_logpowspec(const float* aFrames,
                      int aNFrames,
                      int aNFFT,
                      int aNorm);

#ifdef __cplusplus
}
#endif

#endif /* __C_SPEECH_FEATURES_H__ */
