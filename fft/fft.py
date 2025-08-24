import pyaudio
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# --- Audio Stream Parameters ---
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 44100
CHUNK = 1024*16

# --- PyAudio Setup ---
p = pyaudio.PyAudio()
stream = p.open(format=FORMAT,
                channels=CHANNELS,
                rate=RATE,
                input=True,
                frames_per_buffer=CHUNK)

# --- Matplotlib Setup ---
fig, ax = plt.subplots()
x_data = np.fft.fftfreq(CHUNK, d=1/RATE)[:CHUNK // 2]
line, = ax.plot(x_data, np.zeros(CHUNK // 2))

set_y_axis_in_log_scale = False

if set_y_axis_in_log_scale:
    ax.set_ylim(1E-1, 1E+5)
    ax.set_yscale('log')
else:
    ax.set_ylim(0, 1E+5)
    
ax.set_xlim(0, RATE / 2)
ax.set_title("Real-Time Audio FFT Spectrum")
ax.set_xlabel("Frequency (Hz)")
ax.set_ylabel("Amplitude")
plt.grid()

# --- Animation Function ---
def update(frame):
    """
    This function is called by FuncAnimation to update the plot.
    """
    try:
        # Read a chunk of audio data
        data = stream.read(CHUNK, exception_on_overflow=False)
        # Convert bytes to a NumPy array
        audio_data = np.frombuffer(data, dtype=np.int16)
        
        # Perform the FFT
        fft_result = np.fft.fft(audio_data)
        
        # Get the magnitude and take only the first half
        fft_magnitude = np.abs(fft_result)[:CHUNK // 2]
        
        # Update the plot line with the new FFT data
        line.set_ydata(fft_magnitude)
        
        return line,
    except IOError as e:
        print(f"Error reading from stream: {e}")
        return line,

# --- Run the Animation ---
try:
    # FuncAnimation creates a loop to call the update function
    ani = FuncAnimation(fig, update, blit=True)
    plt.show()
finally:
    # Cleanup resources
    stream.stop_stream()
    stream.close()
    p.terminate()