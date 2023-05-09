#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

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
  char *_factorial
      = (char *)calloc (number * floor (log10 (number) + 1) + 2, 1);
  factorial (number, _factorial);
  PyObject *ret = Py_BuildValue ("s", _factorial);
  free (_factorial);
  return ret;
}

static PyObject *
arithmetica_find_roots_of_polynomial (PyObject *self, PyObject *args)
{
  /*
  find_roots_of_polynomial (const char **coefficients, unsigned long long size,
                          size_t *exact_roots_found);
  */

  /*
   Example call in Python:
     arithmetica.find_roots_of_polynomial(["1", "2", "3"]) ==> ["-1", "-2"]
     Input: List
     Output: Tuple
   */

  PyObject *coefficients_py;
  if (!PyArg_ParseTuple (args, "O", &coefficients_py))
    {
      return NULL;
    }
  const char **coefficients
      = (const char **)malloc (PyList_Size (coefficients_py) * sizeof (char *));
  for (size_t i = 0; i < PyList_Size (coefficients_py); i++)
    {
      PyObject *item = PyList_GetItem (coefficients_py, i);
      coefficients[i] = (char *)malloc (strlen (PyUnicode_AsUTF8 (item)) + 1);
      strcpy (coefficients[i], PyUnicode_AsUTF8 (item));
    }

  // Get the size of the list.
  size_t size = PyList_Size (coefficients_py);

  size_t answer_size;
  struct fraction **answer
      = find_roots_of_polynomial (coefficients, size, &answer_size);

  // List of strings to return.
  PyObject *ret = PyList_New (answer_size);
  for (size_t i = 0; i < answer_size; i++)
    {
      char *str = malloc (strlen (answer[i]->numerator)
                          + strlen (answer[i]->denominator) + 2);
      strcpy (str, answer[i]->numerator);
      if (strcmp (answer[i]->denominator, "1") != 0)
        {
          strcat (str, "/");
          strcat (str, answer[i]->denominator);
        }
      PyList_SetItem (ret, i, Py_BuildValue ("s", str));
      free (str);
      delete_fraction (*answer[i]);
    }
  free (answer);
  // Free the coefficients.
  for (size_t i = 0; i < size; i++)
    {
      free (coefficients[i]);
    }
  free (coefficients);

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
  unsigned long long length;
  char **answer
      = fraction_to_continued_fraction (numerator, denominator, &length);
  char *answer_str;
  if (length > 1)
    {
      // [c1; c2, c3, c4, c5, c6, c7, c8, c9, c10, ...]
      answer_str = (char *)malloc (
          length * (strlen (numerator) + strlen (denominator) + 5) + 3);
      // Hopefully this is enough space for everything.
      // If not, we'll have to reallocate.
      strcpy (answer_str, "[");
      size_t characters_available
          = length * (strlen (numerator) + strlen (denominator) + 5) + 3;
      strcat (answer_str, answer[0]);
      strcat (answer_str, "; ");
      size_t characters_written = strlen (answer[0]) + 2;
      free (answer[0]);
      for (unsigned long long i = 1; i < length; i++)
        {
          // If we're out of space, reallocate.
          if (characters_written + strlen (answer[i]) + 2
              > characters_available)
            {
              characters_available *= 2;
              answer_str = (char *)realloc (answer_str, characters_available);
            }
          characters_written += strlen (answer[i]) + 2;
          strcat (answer_str, answer[i]);
          if (i != length - 1)
            strcat (answer_str, ", ");
          free (answer[i]);
        }
      strcat (answer_str, "]");
    }
  else
    {
      answer_str = (char *)malloc (strlen (answer[0]) + 1);
      strcpy (answer_str, answer[0]);
      free (answer[0]);
    }
  PyObject *ret = Py_BuildValue ("s", answer_str);
  free (answer);
  free (answer_str);
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

static PyObject *
arithmetica_construct_regular_polygon (PyObject *self, PyObject *args)
{
  int n;
  const char *len;
  size_t accuracy;
  if (!PyArg_ParseTuple (args, "isn", &n, &len, &accuracy))
    {
      return NULL;
    }
  struct point *points = construct_regular_polygon (n, len, accuracy);

  PyObject *lst = PyList_New (n);
  for (int i = 0; i < n; i++)
    {
      PyObject *tup = Py_BuildValue ("(ss)", points[i].x, points[i].y);
      PyList_SET_ITEM (lst, i, tup);
      free (points[i].x);
      free (points[i].y);
    }
  free (points);

  return lst;
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
  { "find_roots_of_polynomial", arithmetica_find_roots_of_polynomial,
    METH_VARARGS, "Finds the exact rational roots of a polynomial function." },
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
  { "construct_regular_polygon", arithmetica_construct_regular_polygon,
    METH_VARARGS, "Constructs an n-sided regular polygon." },
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