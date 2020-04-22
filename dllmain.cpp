// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Python.h>  
//#include <structmember.h>
void fly(const char *name, const char *dest, const long k)
{
  printf("%s is flying to %s in %i days.\n", name, dest, k);
}

static PyObject *bird_fly(PyObject *self, PyObject *args)
{
  const char *name, *dest;
  long k;
  if (!PyArg_ParseTuple(args, "ssl", &name, &dest, &k))
    return NULL;
  fly(name, dest, k);

  Py_INCREF(Py_None);
  return Py_None;
}

static PyMethodDef bird_methods[] = {
    { "fly", bird_fly, METH_VARARGS, "Bird fly" },
{ NULL, NULL, 0, NULL }
};
static struct PyModuleDef cModPyDem =
{
    PyModuleDef_HEAD_INIT,
    "bird", /* name of module */
    "",          /* module documentation, may be NULL */
    -1,          /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    bird_methods
};

PyMODINIT_FUNC PyInit_bird(void)
{
  return PyModule_Create(&cModPyDem);
}

//PyMODINIT_FUNC initbird(void)
//{
//  PyImport_AddModule("bird");
//  Py_InitModule("bird", bird_methods);
//}
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

