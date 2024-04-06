import math
import numpy as np
import pyaudio

def note_to_frequency(note):
    notes = {'C': -9, 'C#': -8, 'Db': -8, 'D': -7, 'D#': -6, 'Eb': -6, 'E': -5, 'F': -4, 'F#': -3, 'Gb': -3,
             'G': -2, 'G#': -1, 'Ab': -1, 'A': 0, 'A#': 1, 'Bb': 1, 'B': 2}

    if len(note) == 1:
        note = note + '4'  # Assume octave 4 if not specified
    else:
        print(note[1])
        octave = int(note[1])
        note = note[0]

    distance_from_a4 = (octave - 4) * 12 + notes[note]
    frequency = 2 ** (distance_from_a4 / 12) * 440
    return frequency

def play_tone(frequency, duration, volume=0.5):
    p = pyaudio.PyAudio()

    # Generate samples
    sample_rate = 44100
    t = np.linspace(0, duration, int(sample_rate * duration), endpoint=False)
    tone = volume * np.sin(2 * np.pi * frequency * t)

    # Open stream
    stream = p.open(format=pyaudio.paFloat32, channels=1, rate=sample_rate, output=True)

    # Play tone
    stream.write(tone.astype(np.float32).tobytes())

    # Close stream
    stream.stop_stream()
    stream.close()
    p.terminate()

# Play all possible notes
notes = ['C', 'C#', 'Db', 'D', 'D#', 'Eb', 'E', 'F', 'F#', 'Gb', 'G', 'G#', 'Ab', 'A', 'A#', 'Bb', 'B']
for note in notes:
    frequency = note_to_frequency(note + '4')  # Assuming octave 4 for demonstration
    print(f"Playing {note}...")
    play_tone(frequency, 0.5)  # Play each note for 0.5 seconds
