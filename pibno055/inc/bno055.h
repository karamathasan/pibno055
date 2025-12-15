#ifndef BNO055_H
#define BNO055_H

#define GYRO_X_LSB 0x14
#define GYRO_Y_LSB 0x16
#define GYRO_Z_LSB 0x18
 
#define ACCEL_X_LSB 0x8
#define ACCEL_Y_LSB 0xA
#define ACCEL_Z_LSB 0xC

#define MAG_X_LSB 0xE
#define MAG_Y_LSB 0x10
#define MAG_Z_LSB 0x12

#define QUAT_W_LSB 0x20
#define QUAT_X_LSB 0x22
#define QUAT_Y_LSB 0x24
#define QUAT_Z_LSB 0x26

#define EULER_X_LSB 0x1A
#define EULER_Y_LSB 0x1C
#define EULER_Z_LSB 0x1E

int init();

int i2c_read_2b(int fd, uint8_t dev_addr, uint8_t reg_addr, uint16_t *out);
int i2c_read_1b(int fd, uint8_t dev_addr, uint8_t reg_addr, uint16_t *out);

float get_gyro_x(int fd, uint8_t dev_addr);
float get_gyro_z(int fd, uint8_t dev_addr);
float get_gyro_z(int fd, uint8_t dev_addr);

float get_accel_x(int fd, uint8_t dev_addr);
float get_accel_z(int fd, uint8_t dev_addr);
float get_accel_z(int fd, uint8_t dev_addr);

float get_mag_x(int fd, uint8_t dev_addr);
float get_mag_z(int fd, uint8_t dev_addr);
float get_mag_z(int fd, uint8_t dev_addr);

// no quaternion yet

float get_euler_x(int fd, uint8_t dev_addr);
float get_euler_z(int fd, uint8_t dev_addr);
float get_euler_z(int fd, uint8_t dev_addr);
#endif