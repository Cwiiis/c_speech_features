void framesig(csf_float* sig,
              unsigned int sig_len,
              int frame_len,
              int frame_step,
              csf_float* winfunc,
              csf_float** frames,
              int* frames_dim1,
              int* frames_dim2);

void deframesig(csf_float* frames,
                int frames_dim1,
                int frames_dim2,
                int siglen,
                int frame_len,
                int frame_step,
                csf_float* winfunc,
                csf_float** signal,
                int* signal_dim1);

void magspec(csf_float* frames,
             int frames_dim1,
             int frames_dim2,
             int NFFT,
             csf_float** magspec,
             int* magspec_dim1,
             int* magspec_dim2);

void powspec(csf_float* frames,
             int frames_dim1,
             int frames_dim2,
             int NFFT,
             csf_float** powspec,
             int* powspec_dim1,
             int* powspec_dim2);

void logpowspec(csf_float* frames,
                int frames_dim1,
                int frames_dim2,
                int NFFT,
                int norm,
                csf_float** logpowspec,
                int* logpowspec_dim1,
                int* logpowspec_dim2);

void preemphasis(const short* signal,
                 unsigned int signal_len,
                 csf_float coeff,
                 csf_float** preemph,
                 int* preemph_dim1);
