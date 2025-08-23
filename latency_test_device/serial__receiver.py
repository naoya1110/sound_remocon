import serial
import time
import matplotlib.pyplot as plt

# シリアルポートの設定
# ここに適切なポート名を設定してください。
# Windows: 'COM3'
# Mac/Linux: '/dev/tty.usbmodemXXXX' や '/dev/ttyACM0' など
ser = serial.Serial(
    port='COM3',
    baudrate=115200,
    timeout=1  # タイムアウト時間（秒）
)

# ポートを開く
try:
    ser.close()
    ser.open()
except serial.SerialException as e:
    print(f"Error opening port: {e}")
    exit()

print(f"Connected to port: {ser.port}")

time_list = []
sw_state_list = []
analog_data_list = []

try:
    while True:
        # データの読み込み
        # 1行ずつ読み込む場合は readline() を使う
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            if line == "end":
                break
            else:
                print(f"Received: {line}")
                elapsed_time, sw_state, analog_read = line.split("\t")
                
                
                time_list.append(int(elapsed_time))
                sw_state_list.append(int(sw_state))
                analog_data_list.append(int(analog_read))
        

except KeyboardInterrupt:
    print("\nProgram terminated by user.")
except Exception as e:
    print(f"An error occurred: {e}")
finally:
    # ポートを閉じる
    if ser.is_open:
        ser.close()
        print("Serial port closed.")

plt.plot(time_list, analog_data_list)
plt.plot(time_list, sw_state_list)
plt.show()
