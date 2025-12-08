#ifndef BNO055_H
#define BNO055_H

#define GYRO_X_LSB
#define GYRO_Y_LSB
#define GYRO_Z_LSB

#define ACCEL_X_LSB
#define ACCEL_Y_LSB
#define ACCEL_Z_LSB

#define MAG_X_LSB
#define MAG_Y_LSB
#define MAG_Z_LSB

#define QUAT_W_LSB
#define QUAT_X_LSB
#define QUAT_Y_LSB
#define QUAT_Z_LSB

#define EULER_X_LSB
#define EULER_Y_LSB
#define EULER_Z_LSB

int init();

int i2c_read_2b(int fd, uint8_t dev_addr, uint8_t reg_addr, uint16_t *out);

#endif