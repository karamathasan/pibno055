#include <bno055.h>

#include <Python.h>

static PyObject* _hello_world(PyObject *self){
    return PyUnicode_FromString("Hello_world");
}

// static PyObject* _get_gyro_x(PyObject *self){
    
// }

static struct PyMethodDef methods[] = {
    {"func_name", (PyCFunction)_hello_world, METH_NDARGS},
    {NULL,NULL}
}
static struc PyModuleDef module = {
    PyMethodDef_HEAD_INIT,
    "pibno055",
    NULL,
    -1,
    methods
}

PyMODINIT_FUNC PyInit_pibno055(void){
    return PyModule_Create(&module);
}