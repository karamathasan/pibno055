#ifndef IMU_CLASS_H
#define IMU_CLASS_H

#include <Python.h>
#include <stdint.h>
// #define SLAVE_ADDR 0x28

typedef struct {
    PyObject_HEAD
    int fd;          // File descriptor for I2C
    uint8_t address; // Device address
} IMUObject;

extern PyTypeObject IMUType;

int IMUType_init(PyObject *module);

#endif