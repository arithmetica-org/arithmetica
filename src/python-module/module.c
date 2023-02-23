#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../library/arithmetica.h"

static PyObject *
arithmetica_arccos (PyObject *self, PyObject *args)
{
  const char *number;
  size_t accuracy;
  if (!PyArg_ParseTuple (args, "sn", &number, &accuracy))
    {
      return NULL;
    }
  char *answer = arccos (number, accuracy);
  PyObject *ret = Py_BuildValue ("s", answer);
  free (answer);
  return ret;
}

static PyObject *
arithmetica_arcsin (PyObject *self, PyObject *args)
{
  const char *number;
  size_t accuracy;
  if (!PyArg_ParseTuple (args, "sn", &number, &accuracy))
    {
      return NULL;
    }
  char *answer = arcsin (number, accuracy);
  PyObject *ret = Py_BuildValue ("s", answer);
  free (answer);
  return ret;
}

static PyObject *
arithmetica_arctan (PyObject *self, PyObject *args)
{
  const char *number;
  size_t accuracy;
  if (!PyArg_ParseTuple (args, "sn", &number, &accuracy))
    {
      return NULL;
    }
  char *answer = arctan (number, accuracy);
  PyObject *ret = Py_BuildValue ("s", answer);
  free (answer);
  return ret;
}

static PyObject *
arithmetica_cosine (PyObject *self, PyObject *args)
{
  const char *number;
  size_t accuracy;
  if (!PyArg_ParseTuple (args, "sn", &number, &accuracy))
    {
      return NULL;
    }
  char *answer = cosine (number, accuracy);
  PyObject *ret = Py_BuildValue ("s", answer);
  free (answer);
  return ret;
}

static PyObject *
arithmetica_exponential (PyObject *self, PyObject *args)
{
  const char *number;
  size_t accuracy;
  if (!PyArg_ParseTuple (args, "sn", &number, &accuracy))
    {
      return NULL;
    }
  char *answer = exponential (number, accuracy);
  PyObject *ret = Py_BuildValue ("s", answer);
  free (answer);
  return ret;
}

static PyObject *
arithmetica_factorial (PyObject *self, PyObject *args)
{
  unsigned long number;
  if (!PyArg_ParseTuple (args, "l", &number))
    {
      return NULL;
    }
  char *_factorial = (char *)calloc (
      number * floor (log10 (number) + 1) + 2, 1);
  factorial (number, _factorial);
  PyObject *ret = Py_BuildValue ("s", _factorial);
  free (_factorial);
  return ret;
}

static PyObject *
arithmetica_fraction_to_continued_fraction (PyObject *self, PyObject *args)
{
  const char *numerator;
  const char *denominator;
  if (!PyArg_ParseTuple (args, "ss", &numerator, &denominator))
    {
      return NULL;
    }
  char *answer = fraction_to_continued_fraction (numerator, denominator);
  PyObject *ret = Py_BuildValue ("s", answer);
  free (answer);
  return ret;
}

static PyObject *
arithmetica_igcd (PyObject *self, PyObject *args)
{
  const char *num1;
  const char *num2;
  if (!PyArg_ParseTuple (args, "ss", &num1, &num2))
    {
      return NULL;
    }
  char *answer = (char *)calloc (strlen (num1) + strlen (num2) + 3, 1);
  igcd (num1, num2, answer);
  PyObject *ret = Py_BuildValue ("s", answer);
  free (answer);
  return ret;
}

static PyObject *
arithmetica_ilcm (PyObject *self, PyObject *args)
{
  const char *num1;
  const char *num2;
  if (!PyArg_ParseTuple (args, "ss", &num1, &num2))
    {
      return NULL;
    }
  char *answer = (char *)calloc (strlen (num1) + strlen (num2) + 3, 1);
  ilcm (num1, num2, answer);
  PyObject *ret = Py_BuildValue ("s", answer);
  free (answer);
  return ret;
}

static PyObject *
arithmetica_natural_logarithm (PyObject *self, PyObject *args)
{
  const char *number;
  size_t accuracy;
  if (!PyArg_ParseTuple (args, "sn", &number, &accuracy))
    {
      return NULL;
    }
  char *answer = natural_logarithm (number, accuracy);
  PyObject *ret = Py_BuildValue ("s", answer);
  free (answer);
  return ret;
}

static PyObject *
arithmetica_power (PyObject *self, PyObject *args)
{
  const char *x;
  const char *n;
  size_t accuracy;
  if (!PyArg_ParseTuple (args, "ssn", &x, &n, &accuracy))
    {
      return NULL;
    }
  char *answer = power (x, n, accuracy);
  PyObject *ret = Py_BuildValue ("s", answer);
  free (answer);
  return ret;
}

static PyObject *
arithmetica_repeating_decimal_to_fraction (PyObject *self, PyObject *args)
{
  const char *num1;
  const char *num2;
  if (!PyArg_ParseTuple (args, "ss", &num1, &num2))
    {
      return NULL;
    }
  char *numerator = (char *)calloc (strlen (num1) + strlen (num2) + 3, 1);
  char *denominator = (char *)calloc (strlen (num1) + strlen (num2) + 3, 1);
  repeating_decimal_to_fraction (num1, num2, numerator, denominator);
  char *answer
      = (char *)calloc (strlen (numerator) + strlen (denominator) + 1, 1);
  strcat (answer, numerator);
  strcat (answer, "/");
  strcat (answer, denominator);
  PyObject *ret = Py_BuildValue ("s", answer);
  free (answer);
  free (numerator);
  free (denominator);
  return ret;
}

static PyObject *
arithmetica_simplify_arithmetic_expression (PyObject *self, PyObject *args)
{
  const char *expression;
  int outputType;
  size_t accuracy;
  if (!PyArg_ParseTuple (args, "sin", &expression, &outputType, &accuracy))
    {
      return NULL;
    }
  char *answer
      = simplify_arithmetic_expression (expression, outputType, accuracy);
  PyObject *ret = Py_BuildValue ("s", answer);
  free (answer);
  return ret;
}

static PyObject *
arithmetica_sine (PyObject *self, PyObject *args)
{
  const char *number;
  size_t accuracy;
  if (!PyArg_ParseTuple (args, "sn", &number, &accuracy))
    {
      return NULL;
    }
  char *answer = sine (number, accuracy);
  PyObject *ret = Py_BuildValue ("s", answer);
  free (answer);
  return ret;
}

static PyObject *
arithmetica_square_root (PyObject *self, PyObject *args)
{
  const char *number;
  size_t accuracy;
  if (!PyArg_ParseTuple (args, "sn", &number, &accuracy))
    {
      return NULL;
    }
  char *answer = square_root (number, accuracy);
  PyObject *ret = Py_BuildValue ("s", answer);
  free (answer);
  return ret;
}

static PyObject *
arithmetica_tangent (PyObject *self, PyObject *args)
{
  const char *number;
  size_t accuracy;
  if (!PyArg_ParseTuple (args, "sn", &number, &accuracy))
    {
      return NULL;
    }
  char *answer = tangent (number, accuracy);
  PyObject *ret = Py_BuildValue ("s", answer);
  free (answer);
  return ret;
}

static PyObject *
arithmetica_terminating_decimal_to_fraction (PyObject *self, PyObject *args)
{
  const char *num;
  if (!PyArg_ParseTuple (args, "s", &num))
    {
      return NULL;
    }
  char *numerator = (char *)calloc (strlen (num) + 3, 1);
  char *denominator = (char *)calloc (strlen (num) + 3, 1);
  terminating_decimal_to_fraction (num, numerator, denominator);
  char *answer
      = (char *)calloc (strlen (numerator) + strlen (denominator) + 1, 1);
  strcat (answer, numerator);
  strcat (answer, "/");
  strcat (answer, denominator);
  PyObject *ret = Py_BuildValue ("s", answer);
  free (answer);
  free (numerator);
  free (denominator);
  return ret;
}

static PyMethodDef arithmetica_methods[] = {
  { "arccos", arithmetica_arccos, METH_VARARGS,
    "Computes the inverse cosine of a number less than 1." },
  { "arcsin", arithmetica_arcsin, METH_VARARGS,
    "Computes the inverse sine of a number less than 1." },
  { "arctan", arithmetica_arctan, METH_VARARGS,
    "Computes the inverse tangent of a number less than 1." },
  { "cosine", arithmetica_cosine, METH_VARARGS,
    "Computes the cosine of a number." },
  { "exponential", arithmetica_exponential, METH_VARARGS,
    "Computes e^x, where e is Euler's number: the base to the natural "
    "logarithm." },
  { "factorial", arithmetica_factorial, METH_VARARGS,
    "Computes the factorial of a number." },
  { "fraction_to_continued_fraction",
    arithmetica_fraction_to_continued_fraction, METH_VARARGS,
    "Converts a non-negative rational fraction to a continued fraction." },
  { "igcd", arithmetica_igcd, METH_VARARGS,
    "Computes the greatest common divisor of two integers." },
  { "ilcm", arithmetica_ilcm, METH_VARARGS,
    "Computes the least common multiple of two integers." },
  { "natural_logarithm", arithmetica_natural_logarithm, METH_VARARGS,
    "Computes the natural logarithm of a non-negative number." },
  { "power", arithmetica_power, METH_VARARGS,
    "Computes x^n, where x and n are two real numbers." },
  { "repeating_decimal_to_fraction", arithmetica_repeating_decimal_to_fraction,
    METH_VARARGS, "Converts a repeating decimal to a rational fraction." },
  { "simplify_arithmetic_expression",
    arithmetica_simplify_arithmetic_expression, METH_VARARGS,
    "Simplifies an arithmetic expression involving the five basic math "
    "operations: addition, subtraction, multiplication, division, and "
    "exponentiation." },
  { "sine", arithmetica_sine, METH_VARARGS, "Computes the sine of a number." },
  { "square_root", arithmetica_square_root, METH_VARARGS,
    "Computes the square root of a non-negative number." },
  { "tangent", arithmetica_tangent, METH_VARARGS,
    "Computes the trigonometric tangent of a number." },
  { "terminating_decimal_to_fraction",
    arithmetica_terminating_decimal_to_fraction, METH_VARARGS,
    "Converts a terminating decimal to a rational fraction." },
  { NULL, NULL, 0, NULL }
};

static struct PyModuleDef arithmeticamodule
    = { PyModuleDef_HEAD_INIT, "arithmetica", /* name of module */
        NULL, /* module documentation, may be NULL */
        -1,   /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
        arithmetica_methods };

PyMODINIT_FUNC
PyInit_arithmetica (void)
{
  return PyModule_Create (&arithmeticamodule);
}
