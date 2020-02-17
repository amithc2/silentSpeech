# silentSpeech
A silent speech recognition model that receives EMG signals as input. 

# Pre-Processing 
ANALOG: Fourth order IIR Butterworth (1.2 - 60 Hz passband) -> 32-bit ADC -> RPi 
DIGITAL: 60-Hz Notch filter 

# Processing 
This occurs in processing.py and is responsible for the pipeline leading into the neural network
