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

static int EigneUtil_init(EigenUtil* Self, PyObject* pArgs)        //构造方法.
{
  int size = -1;
  if (!PyArg_ParseTuple(pArgs, "i", &size)) {
    return -1;
  }
  Self->a.resize(size, size);
  Self->b.resize(size, size);

  Self->a.setRandom();
  Self->b.setRandom();

  std::cout << __FILE__ << ":" << __LINE__ << ": a= \n" << Self->a << std::endl;
  std::cout << __FILE__ << ":" << __LINE__ << ": b= \n" << Self->b << std::endl;
  return 0;
}

static void EigneUtil_deconstruct(EigenUtil* Self)        //析构方法.
{
  std::cout << __FILE__ << ":" << __LINE__ << ":" << "release\n";
  Py_TYPE(Self)->tp_free((PyObject*)Self);
  return;
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

static PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "module_class",
    "Python interface for Matrix calculation",
    -1,
    NULL, NULL, NULL, NULL, NULL
};
static PyTypeObject EigenMatrixType = { 0 };
PyMODINIT_FUNC PyInit_module_class(void)       //模块外部名称为--PyVcam
{
  PyObject* pReturn = 0;
  
  EigenMatrixType.ob_base = { PyObject_HEAD_INIT(nullptr) 0 };
  EigenMatrixType.tp_name = "module_class.matrix";
  EigenMatrixType.tp_basicsize = sizeof(EigenUtil);
  EigenMatrixType.tp_dealloc = (destructor)EigneUtil_deconstruct;
  EigenMatrixType.tp_str = PyMatrix_str;
  EigenMatrixType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  EigenMatrixType.tp_new = PyType_GenericNew;       //此类的new内置函数—建立对象.
  EigenMatrixType.tp_doc = "test eigen usage";
  EigenMatrixType.tp_init = (initproc)EigneUtil_init;
  EigenMatrixType.tp_version_tag = 1;

  if (PyType_Ready(&EigenMatrixType) < 0)
    return NULL;

  pReturn = PyModule_Create(&module);
  if (pReturn == NULL)
    return NULL;
  Py_INCREF(&EigenMatrixType);
  PyModule_AddObject(pReturn, "module_class", (PyObject*)&EigenMatrixType); //将这个类加入到模块的Dictionary中.

  return pReturn;
}