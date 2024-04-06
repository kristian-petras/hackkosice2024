import subprocess
import os

def convert_to_wav(input_file):
    # Check if the input file is an MP3, and convert it to WAV if necessary
    filename, file_extension = os.path.splitext(input_file)
    if file_extension.lower() == '.mp3':
        temporary_wav = f'{filename}_temp.wav'
        subprocess.run(['ffmpeg', '-y','-i', input_file, temporary_wav], check=True)
        return temporary_wav
    return input_file

def apply_filters_with_ffmpeg(input_file, output_file, cutoff_frequency):
    # Construct the FFmpeg command
    command = [
        'ffmpeg',
        '-y',
        '-i', input_file,  # Input file
        '-af', f'lowpass=f={cutoff_frequency},loudnorm=I=-16:LRA=11:TP=-1.5',  # Audio filters
        '-ar', '8000',  # Set sample rate to 8 kHz
        '-acodec', 'pcm_u8',  # Use unsigned 8-bit PCM codec for WAV output
        output_file  # Output file
    ]

    try:
        # Execute the FFmpeg command
        subprocess.run(command, check=True)
        print("FFmpeg operation successful.")
    except subprocess.CalledProcessError as e:
        print("FFmpeg error:", e)

def clean_up_temporary_file(temporary_file):
    if os.path.exists(temporary_file):
        os.remove(temporary_file)

# Example usage
input_file = 'input.mp3'  # This can be either WAV or MP3
output_file = 'output.wav'  # Change to 'output.mp3' if you prefer MP3 output
cutoff_frequency = 4000  # Cutoff frequency for the low-pass filter in Hz

# Convert to WAV if the input is MP3
temporary_wav = convert_to_wav(input_file)

# Apply filters
apply_filters_with_ffmpeg(temporary_wav, output_file, cutoff_frequency)


