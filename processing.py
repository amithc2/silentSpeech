import numpy as np
from scipy import signal as scipy
from numpy.random import randn

''' This function implements ICA to remove artifacts -
        Parameters: np array - noisy signal

        Returns: np array that represents a signal with movement artifacts removed'''
def ICA(signal):
    pass

''' This function implements a running average filter that removes spikes that are above
the nearest neighbor 4 neighbors average values -
    Parameters: np array - noisy signal

    Returns: np array that represents a signal with impulses removed'''
def runningFilter(signal):
    pass

''' This function implements a 60 Hz Notch filter -
    Parameters: np array - signal, list - passband, list - stopband

    Returns: np array that represents a filtered signal'''
def notchFilter(signal):
    pass

''' This function implements a MFCC based representation of the signal-
    Parameters: np array - signal

    Returns: np array that represents input to conv net'''
def MFCC(signal): 
    ''' This internal function implements a the framing of the signal for MFCC-
        Parameters: np array - signal, float - window, float - step

        Returns: np array of the windowed signal'''
        # Need to look into returning versus yield in python
        def Frame(signal, window, step):
            pass
    ''' This internal function implements a the framing of the signal for MFCC-
        Parameters: np array - frame

        Returns: np array of periodogram estimate of power spec'''
        def periodEstimate(frame):
            pass
        pass
