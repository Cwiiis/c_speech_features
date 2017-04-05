#!/usr/bin/python
# -*- coding: utf-8 -*-

import c_speech_features as csf
import python_speech_features as psf
import scipy.io.wavfile as wav
import numpy as np
from datetime import datetime

acceptable_error = 1.0002
speed_test_iterations = 250

def time(callback):
    before = datetime.utcnow()
    for i in range(speed_test_iterations):
        callback()
    return (datetime.utcnow() - before).total_seconds()

def print_error(error, msg='Error magnitude'):
    if error <= acceptable_error:
        print ' ✓ - %s: %f' % (msg, error)
        return True
    else:
        print ' 🗴 - %s: %f' % (msg, error)
        return False

def error2d(a, b):
    max_error = 0.0
    for i in range(np.shape(a)[0]):
        for j in range(np.shape(a)[1]):
            error = get_error(a[i][j], b[i][j])
            if error > max_error:
                max_error = error
    if print_error(max_error, 'Max error magnitude') is False:
        print a
        print '----------'
        print b

def error1d(a, b):
    max_error = 0.0
    for i in range(np.shape(a)[0]):
        error = get_error(a[i], b[i])
        if error > max_error:
            max_error = error
    if print_error(max_error, 'Max error magnitude') is False:
        print a
        print '----------'
        print b

def get_error(a, b):
    # TODO: Something better than this
    a = abs(a) + 1
    b = abs(b) + 1
    return max(a, b) / min(a, b)

fs, audio = wav.read('test.wav')

print 'Testing c_speech_features against python_speech_features'
print 'Acceptable error: %f' % (acceptable_error)

print ''
print 'mfcc'
print '===='
psf_mfcc = psf.mfcc(audio)
csf_mfcc = csf.mfcc(audio)
assert(np.shape(psf_mfcc) == np.shape(csf_mfcc))
error2d(psf_mfcc, csf_mfcc)

print ''
print 'fbank'
print '====='
psf_feat, psf_energy = psf.fbank(audio)
csf_feat, csf_energy = csf.fbank(audio)
assert(np.shape(psf_feat) == np.shape(csf_feat))
assert(np.shape(psf_energy) == np.shape(csf_energy))
print 'Features'
error2d(psf_feat, csf_feat)
print 'Energy'
error1d(psf_energy, csf_energy)

print ''
print 'logfbank'
print '========'
psf_feat = psf.logfbank(audio)
csf_feat = csf.logfbank(audio)
assert(np.shape(psf_feat) == np.shape(csf_feat))
error2d(psf_feat, csf_feat)

print ''
print 'ssc'
print '==='
psf_ssc = psf.ssc(audio)
csf_ssc = csf.ssc(audio)
assert(np.shape(psf_ssc) == np.shape(csf_ssc))
error2d(psf_ssc, csf_ssc)

print ''
print 'hz2mel'
print '======'
assert(get_error(psf.hz2mel(8000), csf.hz2mel(8000)) <= acceptable_error)
assert(get_error(psf.hz2mel(16000), csf.hz2mel(16000)) <= acceptable_error)
assert(get_error(csf.mel2hz(csf.hz2mel(8000)), 8000) <= acceptable_error)
print ' ✓'

print ''
print 'mel2hz'
print '======'
assert(get_error(psf.mel2hz(2595), csf.mel2hz(2595)) <= acceptable_error)
assert(get_error(csf.mel2hz(5190), csf.mel2hz(5190)) <= acceptable_error)
assert(get_error(csf.hz2mel(csf.mel2hz(2595)), 2595) <= acceptable_error)
print ' ✓'

print ''
print 'get_filterbanks'
print '==============='
psf_filterbanks = psf.get_filterbanks()
csf_filterbanks = csf.get_filterbanks()
assert(np.shape(psf_filterbanks) == np.shape(csf_filterbanks))
error2d(psf_filterbanks, csf_filterbanks)

print ''
print 'lifter'
print '======'
psf_lifter = psf.lifter(psf_feat)
csf_lifter = csf.lifter(np.array(psf_feat, dtype=np.float32))
assert(np.shape(psf_lifter) == np.shape(csf_lifter))
error2d(psf_lifter, csf_lifter)

print ''
print 'delta'
print '====='
psf_delta = psf.delta(psf_mfcc, 3)
csf_delta = csf.delta(np.array(psf_mfcc, dtype=np.float32), 3)
assert(np.shape(psf_delta) == np.shape(csf_delta))
error2d(psf_delta, csf_delta)

print ''
print 'Testing sigproc'

print ''
print 'framesig'
print '========'
psf_framesig = psf.sigproc.framesig(audio, frame_len=0.025*16000, frame_step=0.01*16000)
csf_framesig = csf.framesig(audio, frame_len=int(0.025*16000), frame_step=int(0.01*16000))
assert(np.shape(psf_framesig) == np.shape(csf_framesig))
error2d(psf_framesig, csf_framesig)

print ''
print 'deframesig'
print '=========='
psf_deframesig = psf.sigproc.deframesig(psf_framesig, len(audio), frame_len=0.025*16000, frame_step=0.01*16000)
csf_deframesig = csf.deframesig(np.array(psf_framesig, dtype=np.float32), len(audio), frame_len=int(0.025*16000), frame_step=int(0.01*16000))
assert(np.shape(psf_deframesig) == np.shape(csf_deframesig))
error1d(psf_deframesig, csf_deframesig)

print ''
print 'magspec'
print '======='
psf_magspec = psf.sigproc.magspec(psf_framesig, 512)
csf_magspec = csf.magspec(np.array(psf_framesig, dtype=np.float32), 512)
assert(np.shape(psf_magspec) == np.shape(csf_magspec))
error2d(psf_magspec, csf_magspec)

print ''
print 'powspec'
print '======='
psf_powspec = psf.sigproc.powspec(psf_framesig, 512)
csf_powspec = csf.powspec(np.array(psf_framesig, dtype=np.float32), 512)
assert(np.shape(psf_powspec) == np.shape(csf_powspec))
error2d(psf_powspec, csf_powspec)

print ''
print 'logpowspec'
print '=========='
psf_logpowspec = psf.sigproc.logpowspec(psf_framesig, 512)
csf_logpowspec = csf.logpowspec(np.array(psf_framesig, dtype=np.float32), 512)
assert(np.shape(psf_logpowspec) == np.shape(csf_logpowspec))
error2d(psf_logpowspec, csf_logpowspec)

print ''
print 'preemphasis'
print '==========='
psf_preemphasis = psf.sigproc.preemphasis(audio)
csf_preemphasis = csf.preemphasis(audio)
assert(np.shape(psf_preemphasis) == np.shape(csf_preemphasis))
error1d(psf_preemphasis, csf_preemphasis)

print ''
print 'Testing speed...'

psf_elapsed = time(lambda: psf.mfcc(audio))
csf_elapsed = time(lambda: csf.mfcc(audio))
print 'mfcc - %.2fx' % (psf_elapsed / csf_elapsed)

psf_elapsed = time(lambda: psf.fbank(audio))
csf_elapsed = time(lambda: csf.fbank(audio))
print 'fbank - %.2fx' % (psf_elapsed / csf_elapsed)

psf_elapsed = time(lambda: psf.logfbank(audio))
csf_elapsed = time(lambda: csf.logfbank(audio))
print 'logfbank - %.2fx' % (psf_elapsed / csf_elapsed)

psf_elapsed = time(lambda: psf.ssc(audio))
csf_elapsed = time(lambda: csf.ssc(audio))
print 'ssc - %.2fx' % (psf_elapsed / csf_elapsed)

psf_elapsed = time(lambda: psf.hz2mel(16000))
csf_elapsed = time(lambda: csf.hz2mel(16000))
print 'hz2mel - %.2fx' % (psf_elapsed / csf_elapsed)

psf_elapsed = time(lambda: psf.mel2hz(5190))
csf_elapsed = time(lambda: csf.mel2hz(5190))
print 'mel2hz - %.2fx' % (psf_elapsed / csf_elapsed)

psf_elapsed = time(lambda: psf.get_filterbanks())
csf_elapsed = time(lambda: csf.get_filterbanks())
print 'get_filterbanks - %.2fx' % (psf_elapsed / csf_elapsed)

psf_elapsed = time(lambda: psf.lifter(psf_feat))
csf_elapsed = time(lambda: csf.lifter(csf_feat))
print 'lifter - %.2fx' % (psf_elapsed / csf_elapsed)

psf_elapsed = time(lambda: psf.delta(psf_mfcc, 3))
csf_elapsed = time(lambda: csf.delta(csf_mfcc, 3))
print 'delta - %.2fx' % (psf_elapsed / csf_elapsed)
