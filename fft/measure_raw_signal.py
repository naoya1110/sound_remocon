import pyaudio
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import datetime
import os

# -- Signal Parameters ---
original_freq = 15250
video_app = "teams"
yyddmm_hhmmss = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
filename = f"raw_signal_{video_app}_{original_freq}Hz_{yyddmm_hhmmss}.csv"
filepath = os.path.join(f"fft/raw_data/{video_app}", filename)

# --- Audio Stream Parameters ---
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 44100
CHUNK = 1024*8


# --- PyAudio Setup ---
p = pyaudio.PyAudio()
stream = p.open(format=FORMAT,
                channels=CHANNELS,
                rate=RATE,
                input=True,
                frames_per_buffer=CHUNK)

# Read a single chunk of audio data
data = stream.read(CHUNK, exception_on_overflow=False)
audio_data = np.frombuffer(data, dtype=np.int16)

# FFT of the single chunk
fft_result = np.fft.fft(audio_data)


# --- Matplotlib Setup ---
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8))

# Subplot 1: Raw Signal (Time Domain)
x_time_data = np.arange(0, CHUNK) / RATE
ax1.plot(x_time_data, audio_data)
ax1.set_ylim(-50, 50)
ax1.set_xlim(0, CHUNK / RATE)
ax1.set_title("Real-Time Audio Signal")
ax1.set_xlabel("Time (s)")
ax1.set_ylabel("Amplitude")
ax1.grid()

# Subplot 2: FFT Spectrum (Frequency Domain)
x_freq_data = np.fft.fftfreq(CHUNK, d=1/RATE)[:CHUNK // 2]
fft_result = np.abs(fft_result)[:CHUNK // 2]
ax2.plot(x_freq_data, fft_result)
ax2.set_ylim(0, 100000)
ax2.set_xlim(0, RATE / 2)
ax2.set_title("Real-Time Audio FFT Spectrum")
ax2.set_xlabel("Frequency (Hz)")
ax2.set_ylabel("Amplitude")
ax2.grid()

plt.tight_layout()
plt.show()

df = pd.DataFrame()
df["time(s)"] = x_time_data
df["sigal"] = audio_data
df.to_csv(filepath, index=False)


stream.stop_stream()
stream.close()
p.terminate()




