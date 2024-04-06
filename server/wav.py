import numpy as np
from scipy.io import wavfile
from scipy.signal import spectrogram

def extract_frequencies(filename):
    wav = _extract_wav(filename)
    frequencies = _extract_frequencies(*wav)
    grouped = _group_frequencies(frequencies)
    return grouped

def _extract_wav(filename):
    sample_rate, data = wavfile.read(filename)
    data = data[:, 0]
    return sample_rate, data

def _extract_frequencies(sample_rate, data, window = 1024):
    frequencies, _, spectrogram_data = spectrogram(data, fs=sample_rate, nperseg=window, noverlap=window//2)
    peak_indices = np.argmax(spectrogram_data, axis=0)
    frequencies = frequencies[peak_indices]

    min_freq = 32
    max_freq = 3000

    frequencies = np.clip(frequencies, min_freq, max_freq)
    frequencies = np.round(frequencies).astype(int)
    return frequencies

def _group_frequencies(frequencies):
    grouped_frequencies = []
    count = 1
    for i in range(len(frequencies)-1):
        if frequencies[i] == frequencies[i+1]:
            count += 1
        else:
            grouped_frequencies.append((frequencies[i], count))
            count = 1
    grouped_frequencies.append((frequencies[-1], count))
    return grouped_frequencies


if __name__ == "__main__":
    wav = _extract_wav("smetana-low-pass-8k-8bit.wav")
    frequencies = _extract_frequencies(*wav)
    grouped_frequencies = _group_frequencies(frequencies)
    print(grouped_frequencies)

