#include <../inc/bno055.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // open()
#include <unistd.h>     // read(), write()
#include <linux/i2c-dev.h>  // I2C_SLAVE
#include <sys/ioctl.h>  // ioctl()
#include <stdint.h>     // uint8_t, uint16_t

#include <Python.h>

typedef struct {
    PyObject_HEAD
    int fd;          // File descriptor for I2C
    uint8_t address; // Device address
} IMUObject;

static int IMU_init(IMUObject *self, PyObject *args, PyObject *kwds)
{
    int bus;
    uint8_t addr;

    if (!PyArg_ParseTuple(args, "ib", &bus, &addr))
        return -1;

    char filename[20];
    snprintf(filename, sizeof(filename), "/dev/i2c-%d", bus);

    int fd = open(filename, O_RDWR);
    if (fd < 0) {
        PyErr_SetFromErrno(PyExc_OSError);
        return -1;
    }

    if (ioctl(fd, I2C_SLAVE, addr) < 0) {
        PyErr_SetFromErrno(PyExc_OSError);
        close(fd);
        return -1;
    }

    self->fd = fd;
    self->address = addr;

    return 0;
}

// class methods

// Gyro wrapper functions
static PyObject* IMU_get_gyro_x(IMUObject *self, PyObject *Py_UNUSED(args)){
    float value = get_gyro_x(self->fd, self->address);
    return PyFloat_FromDouble(value);
}

static PyObject* IMU_get_gyro_y(IMUObject *self, PyObject *Py_UNUSED(args)){
    float value = get_gyro_y(self->fd, self->address);
    return PyFloat_FromDouble(value);
}

static PyObject* IMU_get_gyro_z(IMUObject *self, PyObject *Py_UNUSED(args)){
    float value = get_gyro_z(self->fd, self->address);
    return PyFloat_FromDouble(value);
}

// Accelerometer wrapper functions
static PyObject* IMU_get_accel_x(IMUObject *self, PyObject *Py_UNUSED(args)){
    float value = get_accel_x(self->fd, self->address);
    return PyFloat_FromDouble(value);
}

static PyObject* IMU_get_accel_y(IMUObject *self, PyObject *Py_UNUSED(args)){
    float value = get_accel_y(self->fd, self->address);
    return PyFloat_FromDouble(value);
}

static PyObject* IMU_get_accel_z(IMUObject *self, PyObject *Py_UNUSED(args)){
    float value = get_accel_z(self->fd, self->address);
    return PyFloat_FromDouble(value);
}

// Magnetometer wrapper functions
static PyObject* IMU_get_mag_x(IMUObject *self, PyObject *Py_UNUSED(args)){
    float value = get_mag_x(self->fd, self->address);
    return PyFloat_FromDouble(value);
}

static PyObject* IMU_get_mag_y(IMUObject *self, PyObject *Py_UNUSED(args)){
    float value = get_mag_y(self->fd, self->address);
    return PyFloat_FromDouble(value);
}

static PyObject* IMU_get_mag_z(IMUObject *self, PyObject *Py_UNUSED(args)){
    float value = get_mag_z(self->fd, self->address);
    return PyFloat_FromDouble(value);
}

// Euler angles wrapper functions
static PyObject* IMU_get_euler_x(IMUObject *self, PyObject *Py_UNUSED(args)){
    float value = get_euler_x(self->fd, self->address);
    return PyFloat_FromDouble(value);
}

static PyObject* IMU_get_euler_y(IMUObject *self, PyObject *Py_UNUSED(args)){
    float value = get_euler_y(self->fd, self->address);
    return PyFloat_FromDouble(value);
}

static PyObject* IMU_get_euler_z(IMUObject *self, PyObject *Py_UNUSED(args)){
    float value = get_euler_z(self->fd, self->address);
    return PyFloat_FromDouble(value);
}



