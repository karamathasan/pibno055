#ifndef IMU_CLASS_H
#define IMU_CLASS_H

#include <Python.h>
#define SLAVE_ADDR 0x28

PyObject* IMU_get_gyro_x();
PyObject* IMU_get_gyro_y();
PyObject* IMU_get_gyro_z();

PyObject* IMU_get_accel_x();
PyObject* IMU_get_accel_y();
PyObject* IMU_get_accel_z();

PyObject* IMU_get_mag_x();
PyObject* IMU_get_mag_y();
PyObject* IMU_get_mag_z();

// no quaternion yet

PyObject* IMU_get_euler_x();
PyObject* IMU_get_euler_y();
PyObject* IMU_get_euler_z();

#endif