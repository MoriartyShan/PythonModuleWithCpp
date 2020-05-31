#include <string>
#include <Eigen/Dense>
#include <Python.h>            
#include <structmember.h>
#include <iostream>
#include <sstream>


typedef struct _EigenUtil{
  PyObject_HEAD;
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> a;
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> b;
} EigenUtil;

static PyMemberDef DataMembers[] = {  
  //类/结构的数据成员类说明 表.   
  //根据官方文档说明此类表必须
  //要要以一个元素全为NULL的数据结构结尾，
  //后面还有一个Method 表也是如此
     { "EigenUtil", T_OBJECT, offsetof(EigenUtil, b), 0, "some usage of eigen matrix" },
     { NULL, NULL, NULL, 0, NULL }
};

static void EigneUtil_init(EigenUtil* Self, PyObject* pArgs)        //构造方法.
{
  int size = -1;
  if (!PyArg_ParseTuple(pArgs, "i", &size)) {
    return;
  }
  Self->a.resize(size, size);
  Self->b.resize(size, size);

  Self->a.setRandom();
  Self->b.setRandom();

  std::cout << __FILE__ << ":" << __LINE__ << ": a= \n" << Self->a << std::endl;
  std::cout << __FILE__ << ":" << __LINE__ << ": a= \n" << Self->b << std::endl;
}

static void EigneUtil_deconstruct(EigenUtil* Self)        //析构方法.
{
  std::cout << __FILE__ << ":" << __LINE__ << ":" << "release";
  Py_TYPE(Self)->tp_free((PyObject*)Self);
}

static PyObject *PyMatrix_str(PyObject  *self) {
  std::stringstream ss;
  ss << "a = \n" << ((EigenUtil*)self)->a << "\nb = \n" << ((EigenUtil*)self)->b;
  return Py_BuildValue("s", ss.str().c_str());
}

PyObject *PyMatrix_size(EigenUtil *self) {
  return Py_BuildValue("i", self->a.rows());
}

static PyGetSetDef MatrixGetSet[] = {
    {"size", (getter)PyMatrix_size, nullptr, nullptr},
    {nullptr} };

static PyTypeObject EigenMatrixType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
    "module_class.matrix",/* For printing, in format "<module>.<name>" */
    sizeof(EigenUtil), 0, /* For allocation */

    /* Methods to implement standard operations */

    (destructor)EigneUtil_deconstruct,
    0,//Py_ssize_t tp_vectorcall_offset;
    nullptr, //getattrfunc tp_getattr;
    nullptr, //setattrfunc tp_setattr;
    nullptr, //PyAsyncMethods *tp_as_async; /* formerly known as tp_compare (Python 2)
                             //       or tp_reserved (Python 3) */
    nullptr, //reprfunc tp_repr;

    /* Method suites for standard classes */

    nullptr, //PyNumberMethods *tp_as_number;
    nullptr, //PySequenceMethods *tp_as_sequence;
    nullptr, //PyMappingMethods *tp_as_mapping;

    /* More standard operations (here for binary compatibility) */

    nullptr, //hashfunc tp_hash;
    nullptr, //ternaryfunc tp_call;
    PyMatrix_str, //reprfunc tp_str;
    nullptr, //getattrofunc tp_getattro;
    nullptr, //setattrofunc tp_setattro;

    /* Functions to access object as input/output buffer */
    nullptr,//PyBufferProcs *tp_as_buffer;

    /* Flags to define presence of optional/expanded features */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,//unsigned long tp_flags;

     "test eigen usage",//const char *tp_doc; /* Documentation string */

    /* Assigned meaning in release 2.0 */
    /* call function for all accessible objects */
    nullptr,//traverseproc tp_traverse;

    /* delete references to contained objects */
    nullptr, //inquiry tp_clear;

    /* Assigned meaning in release 2.1 */
    /* rich comparisons */
    nullptr, ///richcmpfunc tp_richcompare;

    /* weak reference enabler */
    0, //Py_ssize_t tp_weaklistoffset;

    /* Iterators */
    nullptr, //getiterfunc tp_iter;
    nullptr, //iternextfunc tp_iternext;

    /* Attribute descriptor and subclassing stuff */
    nullptr, //struct PyMethodDef *tp_methods;
    nullptr, //struct PyMemberDef *tp_members;
    nullptr, //struct PyGetSetDef *tp_getset;
    nullptr, //struct _typeobject *tp_base;
    nullptr, //PyObject *tp_dict;
   nullptr, // descrgetfunc tp_descr_get;
    nullptr, //descrsetfunc tp_descr_set;
    0, //Py_ssize_t tp_dictoffset;
    (initproc)EigneUtil_init,// initproc tp_init;
    nullptr, //allocfunc tp_alloc;
    nullptr,//newfunc tp_new;
    nullptr, //freefunc tp_free; /* Low-level free-memory routine */
    nullptr, //inquiry tp_is_gc; /* For PyObject_IS_GC */
    nullptr, //PyObject *tp_bases;
    nullptr, //PyObject *tp_mro; /* method resolution order */
    nullptr, //PyObject *tp_cache;
    nullptr, //PyObject *tp_subclasses;
    nullptr, //PyObject *tp_weaklist;
    nullptr, //destructor tp_del;

    /* Type attribute cache version tag. Added in version 2.6 */
    1,//unsigned int tp_version_tag;

    nullptr, //destructor tp_finalize;
    nullptr, //dvectorcallfunc tp_vectorcall;

    /* bpo-37250: kept for backwards compatibility in CPython 3.8 only */
    //Py_DEPRECATED(3.8)// nullptr//int(*tp_print)(PyObject *, FILE *, int);
};

static PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "module_class",
    "Python interface for Matrix calculation",
    -1,
    NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC PyInit_module_class(void)       //模块外部名称为--PyVcam
{
  PyObject* pReturn = 0;
  EigenMatrixType.tp_new = PyType_GenericNew;       //此类的new内置函数—建立对象.


  if (PyType_Ready(&EigenMatrixType) < 0)
    return NULL;

  pReturn = PyModule_Create(&module);
  if (pReturn == NULL)
    return NULL;
  Py_INCREF(&EigenMatrixType);
  PyModule_AddObject(pReturn, "module_class", (PyObject*)&EigenMatrixType); //将这个类加入到模块的Dictionary中.

  return pReturn;
}