// NOTE: For reliable operation on a Raspberry Pi, enable the i2c-gpio
//   overlay and use the I2C device it provides (usually /dev/i2c-3).
// NOTE: You might need to change the 'const char * device' line below
//   to specify the correct I2C device.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // open()
#include <unistd.h>     // read(), write()
#include <linux/i2c-dev.h>  // I2C_SLAVE
#include <sys/ioctl.h>  // ioctl()
#include <stdint.h>     // uint8_t, uint16_t


int init(){
    int file;
    int adapter_nr = 3; /* probably dynamically determined */
    char filename[20];

    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);
    if (file < 0) {
        /* ERROR HANDLING; you can check errno to see what went wrong */
        perror("Failed to open I2C bus. error:%d", file);
        return(-1);
    }

    return file;
}

int i2c_read_2b(int fd, uint8_t dev_addr, uint8_t reg_addr, int16_t *out)
{
    uint8_t buf[2];

    struct i2c_msg msgs[2];

    //define the write address
    msgs[0].addr  = dev_addr;
    msgs[0].flags = 0;        
    msgs[0].len   = 1;
    msgs[0].buf   = &reg_addr;

    //read the data
    msgs[1].addr  = dev_addr;
    msgs[1].flags = I2C_M_RD; 
    msgs[1].len   = 2;
    msgs[1].buf   = buf;

    struct i2c_rdwr_ioctl_data ioctl_data = {
        .msgs  = msgs,
        .nmsgs = 2
    };

    if (ioctl(fd, I2C_RDWR, &ioctl_data) < 0) {
        perror("I2C_RDWR");
        return -1;
    }

    *out = (int16_t)(buf[0] | (buf[1] << 8));
    return 0;
}

int i2c_read_1b(int fd, uint8_t dev_addr, uint8_t reg_addr, int16_t *out)
{
    uint8_t buf[1];

    struct i2c_msg msgs[2];

    //define the write address
    msgs[0].addr  = dev_addr;
    msgs[0].flags = 0;        
    msgs[0].len   = 1;
    msgs[0].buf   = &reg_addr;

    //read the data
    msgs[1].addr  = dev_addr;
    msgs[1].flags = I2C_M_RD; 
    msgs[1].len   = 2;
    msgs[1].buf   = buf;

    struct i2c_rdwr_ioctl_data ioctl_data = {
        .msgs  = msgs,
        .nmsgs = 2
    };

    if (ioctl(fd, I2C_RDWR, &ioctl_data) < 0) {
        perror("I2C_RDWR");
        return -1;
    }

    *out = (int16_t)(buf[0]);
    return 0;
}

float get_euler_x(int fd, uint8_t dev_addr){
    int16_t* raw;
    i2c_read_2b(fd, dev_addr, EULER_X_LSB, raw)

    float x = raw / 16.0f;
    return x;
}

float get_euler_y(int fd, uint8_t dev_addr){
    int16_t* raw;
    i2c_read_2b(fd, dev_addr, EULER_Y_LSB, raw)

    float y = raw / 16.0f;
    return y;
}

float get_euler_z(int fd, uint8_t dev_addr){
    int16_t* raw;
    i2c_read_2b(fd, dev_addr, EULER_Z_LSB, raw)

    float z = raw / 16.0f;
    return z;
}

float get_gyro_x(int fd, uint8_t dev_addr){
    int16_t* raw;
    i2c_read_2b(fd, dev_addr, GYRO_X_LSB, raw)

    float x = raw / 16.0f;
    return x;
}

float get_gyro_y(int fd, uint8_t dev_addr){
    int16_t* raw;
    i2c_read_2b(fd, dev_addr, GYRO_Y_LSB, raw)

    float y = raw / 16.0f;
    return y;
}

float get_gyro_z(int fd, uint8_t dev_addr){
    int16_t* raw;
    i2c_read_2b(fd, dev_addr, GYRO_Z_LSB, raw)

    float z = raw / 16.0f;
    return z;
}

float get_accel_x(int fd, uint8_t dev_addr){
    int16_t* raw;
    i2c_read_2b(fd, dev_addr, ACCEL_X_LSB, raw)

    float x = raw / 100.0f;
    return x;
}

float get_accel_y(int fd, uint8_t dev_addr){
    int16_t* raw;
    i2c_read_2b(fd, dev_addr, ACCEL_Y_LSB, raw)

    float y = raw / 100.0f;
    return y;
}

float get_accel_z(int fd, uint8_t dev_addr){
    int16_t* raw;
    i2c_read_2b(fd, dev_addr, ACCEL_Z_LSB, raw)

    float z = raw / 100.0f;
    return z;
}


float get_mag_x(int fd, uint8_t dev_addr){
    int16_t* raw;
    i2c_read_2b(fd, dev_addr, MAG_X_LSB, raw)

    float x = raw / 16.0;
    return x;
}

float get_mag_y(int fd, uint8_t dev_addr){
    int16_t* raw;
    i2c_read_2b(fd, dev_addr, MAG_Y_LSB, raw)

    float y = raw / 16.0;
    return y;
}

float get_mag_z(int fd, uint8_t dev_addr){
    int16_t* raw;
    i2c_read_2b(fd, dev_addr, MAG_Z_LSB, raw)

    float z = raw / 16.0;
    return z;
}

