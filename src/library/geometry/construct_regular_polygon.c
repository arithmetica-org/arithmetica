#include "point.h"
#include <arithmetica.h>
#include <basic_math_operations.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <truncate.h>

struct point *
construct_regular_polygon (size_t n, const char *length, size_t accuracy)
{
  struct point *polygon = malloc (n * sizeof (struct point));

  // First two initial points.
  polygon[0].x = (char *)calloc (2, 1);
  polygon[0].y = (char *)calloc (2, 1);
  polygon[1].x = (char *)calloc (strlen (length) + 1, 1);
  polygon[1].y = (char *)calloc (2, 1);
  strcpy (polygon[0].x, "0");
  strcpy (polygon[0].y, "0");
  strcpy (polygon[1].x, length);
  strcpy (polygon[1].y, "0");

  // Since tan(90°) is undefined, this becomes an edge case.
  if (n == 4)
    {
      polygon[2].x = (char *)calloc (strlen (length) + 1, 1);
      polygon[2].y = (char *)calloc (strlen (length) + 1, 1);
      polygon[3].x = (char *)calloc (2, 1);
      polygon[3].y = (char *)calloc (strlen (length) + 1, 1);
      strcpy (polygon[2].x, length);
      strcpy (polygon[2].y, length);
      strcpy (polygon[3].x, "0");
      strcpy (polygon[3].y, length);
      return polygon;
    }

  // Convert [n] to a string. Note that we're assuming that n > 0.
  size_t n_copy = n;
  size_t num_digits = floor (log10 (n)) + 1;
  char *n_str = (char *)malloc (num_digits + 1);
  for (size_t i = 0; i < num_digits; ++i)
    {
      n_str[num_digits - i - 1] = '0' + n_copy % 10;
      n_copy /= 10;
    }
  n_str[num_digits] = '\0';

  char *pi_by_6 = arcsin ("0.5", accuracy);
  char *two_pi = (char *)calloc (strlen (pi_by_6) + 5, 1);
  multiply ("12", pi_by_6, two_pi);
  char *angle_in_radians
      = (char *)calloc (strlen (two_pi) + num_digits + accuracy + 3, 1);
  divide (two_pi, n_str, angle_in_radians, accuracy);
  char *tan_ext_angle = tangent (angle_in_radians, accuracy);
  free (pi_by_6);

  for (size_t i = 0; i < n - 2; ++i)
    {
      // Compute the slope of the initial line.
      char *buf_1 = (char *)calloc (
          strlen (polygon[i].y) + strlen (polygon[i + 1].y) + 3, 1);
      char *buf_2 = (char *)calloc (
          strlen (polygon[i].x) + strlen (polygon[i + 1].x) + 3, 1);
      subtract (polygon[i].y, polygon[i + 1].y, buf_1);
      subtract (polygon[i].x, polygon[i + 1].x, buf_2);
      char *slope_initial_line
          = (char *)calloc (strlen (buf_1) + strlen (buf_2) + accuracy + 3, 1);
      divide (buf_1, buf_2, slope_initial_line, accuracy);

      // Compute the slope and intercept of the new line.
      char *buf_3 = (char *)calloc (
          strlen (slope_initial_line) + strlen (tan_ext_angle) + 3, 1);
      char *buf_4 = (char *)calloc (
          strlen (slope_initial_line) + strlen (tan_ext_angle) + 3, 1);
      add (slope_initial_line, tan_ext_angle, buf_3);
      multiply (slope_initial_line, tan_ext_angle, buf_4);
      char *buf_5 = (char *)calloc (strlen (buf_4) + 4, 1);
      subtract ("1", buf_4, buf_5);
      char *slope_new_line
          = (char *)calloc (strlen (buf_3) + strlen (buf_5) + accuracy + 3, 1);
      divide (buf_3, buf_5, slope_new_line, accuracy);
      char *buf_6 = (char *)calloc (
          strlen (slope_new_line) + strlen (polygon[i + 1].x) + 3, 1);
      multiply (slope_new_line, polygon[i + 1].x, buf_6);
      char *intercept_new_line
          = (char *)calloc (strlen (polygon[i + 1].y) + strlen (buf_6) + 3, 1);
      subtract (polygon[i + 1].y, buf_6, intercept_new_line);

      // Compute candidate intersection points.
      char *buf_7 = (char *)calloc (2 * strlen (slope_new_line) + 3, 1);
      multiply (slope_new_line, slope_new_line, buf_7);
      char *buf_8 = (char *)calloc (strlen (buf_7) + 4, 1);
      add (buf_7, "1", buf_8);
      char *buf_9 = square_root (buf_8, accuracy);
      char *buf_10 = (char *)calloc (
          strlen (length) + strlen (buf_9) + accuracy + 3, 1);
      divide (length, buf_9, buf_10, accuracy);
      char *x_1 = (char *)calloc (
          strlen (polygon[i + 1].x) + strlen (buf_10) + 3, 1);
      char *x_2 = (char *)calloc (
          strlen (polygon[i + 1].x) + strlen (buf_10) + 3, 1);
      add (polygon[i + 1].x, buf_10, x_1);
      subtract (polygon[i + 1].x, buf_10, x_2);
      char *buf_11
          = (char *)calloc (strlen (x_1) + strlen (slope_new_line) + 3, 1);
      char *buf_12
          = (char *)calloc (strlen (x_2) + strlen (slope_new_line) + 3, 1);
      multiply (slope_new_line, x_1, buf_11);
      multiply (slope_new_line, x_2, buf_12);
      char *y_1 = (char *)calloc (
          strlen (buf_11) + strlen (intercept_new_line) + 3, 1);
      char *y_2 = (char *)calloc (
          strlen (buf_12) + strlen (intercept_new_line) + 3, 1);
      add (buf_11, intercept_new_line, y_1);
      add (buf_12, intercept_new_line, y_2);

      // Add new point to polygon after determining the correct point.
      // To decide the correct x,y pair, notice that y is never decreasing for
      // the first n / 2 sides, and is always decreasing after that.
      if (i + 1 > n / 2)
        {
          char *sub_buf = (char *)calloc (
              strlen (polygon[i + 1].y) + strlen (y_1) + 3, 1);
          subtract (polygon[i + 1].y, y_1, sub_buf);
          if ((!strcmp (polygon[i + 1].y, y_1)) || sub_buf[0] == '-')
            {
              size_t x2_buf_size = strlen (x_2) + 1;
              size_t y2_buf_size = strlen (y_2) + 1;

              polygon[i + 2].x = (char *)malloc (x2_buf_size);
              polygon[i + 2].y = (char *)malloc (y2_buf_size);
              memcpy (polygon[i + 2].x, x_2, x2_buf_size);
              memcpy (polygon[i + 2].y, y_2, y2_buf_size);
            }
          else
            {
              size_t x1_buf_size = strlen (x_1) + 1;
              size_t y1_buf_size = strlen (y_1) + 1;

              polygon[i + 2].x = (char *)malloc (x1_buf_size);
              polygon[i + 2].y = (char *)malloc (y1_buf_size);
              memcpy (polygon[i + 2].x, x_1, x1_buf_size);
              memcpy (polygon[i + 2].y, y_1, y1_buf_size);
            }
          free (sub_buf);
        }
      else
        {
          if (!strcmp (y_1, y_2))
            {
              char *sub_buf
                  = (char *)calloc (strlen (x_1) + strlen (x_2) + 3, 1);
              subtract (x_1, x_2, sub_buf);
              if (sub_buf[0] == '-')
                {
                  size_t x1_buf_size = strlen (x_1) + 1;
                  size_t y1_buf_size = strlen (y_1) + 1;

                  polygon[i + 2].x = (char *)malloc (x1_buf_size);
                  polygon[i + 2].y = (char *)malloc (y1_buf_size);
                  memcpy (polygon[i + 2].x, x_1, x1_buf_size);
                  memcpy (polygon[i + 2].y, y_1, y1_buf_size);
                }
              else
                {
                  size_t x2_buf_size = strlen (x_2) + 1;
                  size_t y2_buf_size = strlen (y_2) + 1;

                  polygon[i + 2].x = (char *)calloc (x2_buf_size, 1);
                  polygon[i + 2].y = (char *)calloc (y2_buf_size, 1);
                  memcpy (polygon[i + 2].x, x_2, x2_buf_size);
                  memcpy (polygon[i + 2].y, y_2, y2_buf_size);
                }
              free (sub_buf);
            }
          else
            {
              char *sub_buf = (char *)calloc (
                  strlen (polygon[i + 1].y) + strlen (y_1) + 3, 1);
              subtract (polygon[i + 1].y, y_1, sub_buf);
              if (!strcmp (polygon[i + 1].y, y_1) || sub_buf[0] == '-')
                {
                  polygon[i + 2].x = (char *)calloc (strlen (x_1) + 1, 1);
                  polygon[i + 2].y = (char *)calloc (strlen (y_1) + 1, 1);
                  strcpy (polygon[i + 2].x, x_1);
                  strcpy (polygon[i + 2].y, y_1);
                }
              else
                {
                  polygon[i + 2].x = (char *)calloc (strlen (x_2) + 1, 1);
                  polygon[i + 2].y = (char *)calloc (strlen (y_2) + 1, 1);
                  strcpy (polygon[i + 2].x, x_2);
                  strcpy (polygon[i + 2].y, y_2);
                }
              free (sub_buf);
            }
        }

      truncate (polygon[i + 2].x, accuracy);
      truncate (polygon[i + 2].y, accuracy);

      free (buf_1);
      free (buf_2);
      free (buf_3);
      free (buf_4);
      free (buf_5);
      free (buf_6);
      free (buf_7);
      free (buf_8);
      free (buf_9);
      free (buf_10);
      free (buf_11);
      free (buf_12);
      free (slope_initial_line);
      free (slope_new_line);
      free (intercept_new_line);
      free (x_1);
      free (x_2);
      free (y_1);
      free (y_2);
    }

  free (n_str);
  free (two_pi);
  free (angle_in_radians);
  free (tan_ext_angle);

  return polygon;
}