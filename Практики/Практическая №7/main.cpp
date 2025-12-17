#include <Python.h>
#include <ctime>

static PyObject* calculate_sum(PyObject* self, PyObject* args) {
    PyObject* listObj;
    if (!PyArg_ParseTuple(args, "O", &listObj)) {
        return NULL;
    }

    long size = PyList_Size(listObj);
    double sum = 0;

    clock_t start = clock();

    for (int i = 0; i < size; i++) {
        PyObject* temp = PyList_GetItem(listObj, i);
        double val = PyFloat_AsDouble(temp);
        sum += val;
    }

    clock_t end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    return Py_BuildValue("d", cpu_time_used);
}

static PyMethodDef SumMethods[] = {
    {"calculate_sum", calculate_sum, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef summodule = {
    PyModuleDef_HEAD_INIT,
    "summodule",
    "",
    -1,
    SumMethods
};

PyMODINIT_FUNC PyInit_summodule(void) {
    return PyModule_Create(&summodule);
}
