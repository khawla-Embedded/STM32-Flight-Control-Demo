
# dashboard.py
import serial
import matplotlib.pyplot as plt
from collections import deque

# Configuration
MAX_POINTS = 50
ser = serial.Serial('COM3', 115200, timeout=1)  # Changez COM3 selon votre port

# Initialisation des graphiques
plt.ion()
fig, (ax1, ax2, ax3) = plt.subplots(3, 1)
fig.suptitle('Flight Data Recorder')

# Buffers circulaires
pitch_data = deque(maxlen=MAX_POINTS)
roll_data = deque(maxlen=MAX_POINTS)
alt_data = deque(maxlen=MAX_POINTS)

while True:
    try:
        line = ser.readline().decode().strip()
        if line:
            pitch, roll, alt, _ = map(float, line.split(','))
            pitch_data.append(pitch)
            roll_data.append(roll)
            alt_data.append(alt)
            
            # Mise à jour des graphiques
            ax1.clear()
            ax1.plot(pitch_data, 'r-')
            ax1.set_ylabel('Pitch (rad)')
            
            ax2.clear()
            ax2.plot(roll_data, 'b-')
            ax2.set_ylabel('Roll (rad)')
            
            ax3.clear()
            ax3.plot(alt_data, 'g-')
            ax3.set_ylabel('Altitude (m)')
            
            plt.pause(0.01)
            
    except KeyboardInterrupt:
        break
    except Exception as e:
        print(f"Error: {e}")

ser.close()
