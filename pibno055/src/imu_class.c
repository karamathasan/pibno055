#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>      // open()
#include <unistd.h>     // read(), write()
#include <linux/i2c-dev.h>  // I2C_SLAVE
#include <sys/ioctl.h>  // ioctl()
#include <stdint.h>     // uint8_t, uint16_t

#include <Python.h>
#include "bno055.h"
#include "imu_class.h"

static int IMU_init(IMUObject *self, PyObject *args, PyObject *kwds)
{
    int bus;
    uint8_t addr;

    if (!PyArg_ParseTuple(args, "ib", &bus, &addr))
        return -1;

    int fd = get_fd(bus);

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

static void IMU_dealloc(IMUObject *self)
{
    if (self->fd >= 0)
        close(self->fd);
    Py_TYPE(self)->tp_free((PyObject *)self);
}

// class methods
static PyObject* IMU_set_mode(IMUObject *self, PyObject *args){
    uint8_t mode = 0x00;
    if (!PyArg_ParseTuple(args, "b", &mode)){
        return NULL;
    }

    set_mode(self->fd, self->address, mode);

    Py_RETURN_NONE;
}

static PyObject* IMU_get_gyro(IMUObject *self, PyObject *Py_UNUSED(args)){
    float x = get_gyro_x(self->fd, self->address);
    float y = get_gyro_y(self->fd, self->address);
    float z = get_gyro_z(self->fd, self->address);

    PyObject *tuple = PyTuple_New(3);  // create a tuple of length 3
    if (!tuple)
        return NULL;  // memory allocation failed

    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(x));  // index 0
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(y));  // index 1
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(z));  // index 2
    return tuple;
}

static PyObject* IMU_get_accel(IMUObject *self, PyObject *Py_UNUSED(args)){
    float x = get_accel_x(self->fd, self->address);
    float y = get_accel_y(self->fd, self->address);
    float z = get_accel_z(self->fd, self->address);

    PyObject *tuple = PyTuple_New(3);  // create a tuple of length 3
    if (!tuple)
        return NULL;  // memory allocation failed

    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(x));  // index 0
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(y));  // index 1
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(z));  // index 2
    return tuple;
}

static PyObject* IMU_get_mag(IMUObject *self, PyObject *Py_UNUSED(args)){
    float x = get_mag_x(self->fd, self->address);
    float y = get_mag_y(self->fd, self->address);
    float z = get_mag_z(self->fd, self->address);

    PyObject *tuple = PyTuple_New(3);  // create a tuple of length 3
    if (!tuple)
        return NULL;  // memory allocation failed

    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(x));  // index 0
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(y));  // index 1
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(z));  // index 2
    return tuple;
}



static PyObject* IMU_get_euler(IMUObject *self, PyObject *Py_UNUSED(args)){
    float x = get_euler_x(self->fd, self->address);
    float y = get_euler_y(self->fd, self->address);
    float z = get_euler_z(self->fd, self->address);

    PyObject *tuple = PyTuple_New(3);  // create a tuple of length 3
    if (!tuple)
        return NULL;  // memory allocation failed

    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(x));  // index 0
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(y));  // index 1
    PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(z));  // index 2
    return tuple;
}


static struct PyMethodDef IMU_methods[] = {
    {"get_gyro", (PyCFunction)IMU_get_gyro, METH_NOARGS},

    {"get_accel", (PyCFunction)IMU_get_accel, METH_NOARGS},

    {"get_mag", (PyCFunction)IMU_get_mag, METH_NOARGS},

    {"get_euler", (PyCFunction)IMU_get_euler, METH_NOARGS},

    {"set_mode", (PyCFunction)IMU_set_mode, METH_VARARGS},
    {NULL,NULL}
};

PyTypeObject IMUType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "pibno055.IMU",
    .tp_basicsize = sizeof(IMUObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "IMU I2C driver",
    .tp_methods = IMU_methods,
    .tp_init = (initproc)IMU_init,
    .tp_new = PyType_GenericNew,
    .tp_dealloc = (destructor)IMU_dealloc
};



