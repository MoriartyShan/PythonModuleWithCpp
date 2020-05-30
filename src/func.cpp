// dllmain.cpp : Defines the entry point for the DLL application.
#include <Python.h>
#include "common.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

static PyObject *call_cpp_main(PyObject *self, PyObject *args) {
  const int arg_number = 2;
  char *argv[arg_number] = {
    nullptr, //process name
    nullptr //leave for glog dir, it is not used when glog is closed
  };
                                    /*process_name, */
  if (!PyArg_ParseTuple(args, "ss", &argv[0], &argv[1])) {
    return NULL;
  }
  call_cpp(argv[0], argv[1]);

  Py_INCREF(Py_None);
  return Py_None;
}

static PyMethodDef main_methods[] = {
    { "call_cpp", call_cpp_main, METH_VARARGS, "call cpp function" },
{ NULL, NULL, 0, NULL }
};
static struct PyModuleDef cModPyDem =
{
    PyModuleDef_HEAD_INIT,
    "module_func", /* name of module */
    "contains module_func",          /* module documentation, may be NULL */
    -1,          /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    main_methods
};

PyMODINIT_FUNC PyInit_module_func(void)
{
  return PyModule_Create(&cModPyDem);
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
