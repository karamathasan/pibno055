#include <bno055.h>
#include <imu_class.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // open()
#include <unistd.h>     // read(), write()
#include <linux/i2c-dev.h>  // I2C_SLAVE
#include <sys/ioctl.h>  // ioctl()
#include <stdint.h>     // uint8_t, uint16_t

#include <Python.h>

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "_pibno055",
    NULL,
    -1,
    NULL
};

PyMODINIT_FUNC PyInit__pibno055(void){
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