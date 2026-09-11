import serial
import time
import ctypes

PORT = "COM3"
BAUD_RATE = 115200

print("Connecting to ESP32...")

try:
    esp32 = serial.Serial(
        PORT,
        BAUD_RATE,
        timeout=1
    )

    time.sleep(2)

    print("================================")
    print("       FOCUSGUARD RUNNING")
    print("================================")
    print("ESP32 connected on", PORT)
    print("Waiting for SLEEP command...")

    while True:

        data = esp32.readline().decode(
            "utf-8",
            errors="ignore"
        ).strip()

        if data:

            print("ESP32:", data)

            if data == "SLEEP":

                print("SLEEP COMMAND RECEIVED")
                print("Putting Windows to sleep...")

                # Windows Sleep
                ctypes.windll.kernel32.SetThreadExecutionState(0x80000000)

                ctypes.windll.PowrProf.SetSuspendState(
                    False,   # Hibernate = False
                    False,   # Force = False
                    False    # Wake events enabled
                )

                time.sleep(10)

except serial.SerialException as e:

    print("Could not connect to ESP32.")
    print("Check that ESP32 is connected to COM3.")
    print("Error:", e)

except KeyboardInterrupt:

    print("\nFocusGuard stopped.")

finally:

    try:
        esp32.close()
    except:
        pass