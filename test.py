import sys
sys.path.insert(0, 'build/lib.linux-aarch64-3.11')

import pibno055

imu = pibno055.IMU(1, 0x28)
imu.set_mode(0x0C)


while True:
    euler = imu.get_euler()  # e.g., returns a tuple like (12.3, 4.5, 6.7)
    line = f"{euler}"
    sys.stdout.write("\r" + " " * 50)  # clear previous line (adjust width if needed)
    sys.stdout.write("\r" + line)
    sys.stdout.flush()
    # sys.stdout.flush()
