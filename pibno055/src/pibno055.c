#include <../inc/bno055.h>
#include <../inc/imu_class.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // open()
#include <unistd.h>     // read(), write()
#include <linux/i2c-dev.h>  // I2C_SLAVE
#include <sys/ioctl.h>  // ioctl()
#include <stdint.h>     // uint8_t, uint16_t

#include <Python.h>

static struct PyMethodDef IMU_methods[] = {
    {"get_gyro_x", (PyCFunction)IMU_get_gyro_x, METH_NOARGS},
    {"get_gyro_y", (PyCFunction)IMU_get_gyro_y, METH_NOARGS},
    {"get_gyro_z", (PyCFunction)IMU_get_gyro_z, METH_NOARGS},

    {"get_accel_x", (PyCFunction)IMU_get_accel_x, METH_NOARGS},
    {"get_accel_y", (PyCFunction)IMU_get_accel_y, METH_NOARGS},
    {"get_accel_z", (PyCFunction)IMU_get_accel_z, METH_NOARGS},

    {"get_mag_x", (PyCFunction)IMU_get_mag_x, METH_NOARGS},
    {"get_mag_y", (PyCFunction)IMU_get_mag_y, METH_NOARGS},
    {"get_mag_z", (PyCFunction)IMU_get_mag_z, METH_NOARGS},

    {"get_euler_x", (PyCFunction)IMU_get_euler_x, METH_NOARGS},
    {"get_euler_y", (PyCFunction)IMU_get_euler_y, METH_NOARGS},
    {"get_euler_z", (PyCFunction)IMU_get_euler_z, METH_NOARGS},
    {NULL,NULL}
};

static void IMU_dealloc(IMUObject *self)
{
    if (self->fd >= 0)
        close(self->fd);
    Py_TYPE(self)->tp_free((PyObject *)self);
}

// type definition
static PyTypeObject IMUType = {
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

static struct PyModuleDef module = {
    PyMethodDef_HEAD_INIT,
    "pibno055",
    NULL,
    -1,
    null
};

PyMODINIT_FUNC PyInit_pibno055(void){
    PyObject *m;
    if (PyType_Ready(&IMUType) < 0)
        return NULL;

    m = PyModule_Create(&module);
    if (!m)
        return NULL;

    Py_INCREF(&IMUType);
    PyModule_AddObject(m, "IMU", (PyObject *)&IMUType);

    return m;
}