#pragma once

#include <cmath>
#include <vector>

#include "../arithmetica.hpp"
#include "point.h"
#include <basic_math_operations.hpp>

namespace construct_regular_polygon_helpers
{
using namespace basic_math_operations;
class PointCpp
{

public:
  BMONum x, y;
  PointCpp () { x = y = 0; }
  PointCpp (BMONum x, BMONum y)
  {
    this->x = x;
    this->y = y;
  }
};

PointCpp GetCorrectPoint (BMONum &x_1, BMONum &y_1, BMONum &x_2, BMONum &y_2,
                          int &i, int n, PointCpp &prev_pt);
PointCpp ChoosePointToLeft (BMONum &x_1, BMONum &y_1, BMONum &x_2,
                            BMONum &y_2);
PointCpp ChooseHigherPoint (BMONum &x_1, BMONum &y_1, BMONum &x_2, BMONum &y_2,
                            PointCpp &prev_pt);
PointCpp ChooseLowerPoint (BMONum &x_1, BMONum &y_1, BMONum &x_2, BMONum &y_2,
                           PointCpp &prev_pt);
void ComputeLine (PointCpp &prev_pt, BMONum &m, BMONum &tan_exterior_angle,
                  BMONum &l, BMONum &s, BMONum &c);
void ComputeIntersectionPoints (PointCpp &prev_pt, BMONum &s, BMONum &c,
                                BMONum &l, BMONum &x_1, BMONum &y_1,
                                BMONum &x_2, BMONum &y_2, size_t accuracy);
point *
ConvertToC (const std::vector<PointCpp> &polygon)
{
  point *points = (point *)malloc (polygon.size () * sizeof (point));
  for (auto i = 0; i < polygon.size (); i++)
    {
      auto &x = polygon[i].x.number;
      auto &y = polygon[i].y.number;
      points[i].x = (char *)malloc (x.length () + 1);
      points[i].y = (char *)malloc (y.length () + 1);
      strcpy (points[i].x, x.c_str ());
      strcpy (points[i].y, y.c_str ());
    }
  return points;
}
}; // namespace construct_regular_polygon_helpers

point *
construct_regular_polygon_cpp (int n, const char *length_c, size_t accuracy)
{
  using namespace arithmetica;
  using namespace basic_math_operations;
  using namespace construct_regular_polygon_helpers;

  BMONum length = std::string (length_c);

  DIVISION_ACCURACY = accuracy;
  std::vector<PointCpp> polygon
      = { PointCpp ("0", "0"), PointCpp (length, "0") };

  // Since tan(90 deg) is undefined, this becomes an edge case.
  if (n == 4)
    {
      polygon.emplace_back (length, length);
      polygon.emplace_back ("0", length);
      return ConvertToC (polygon);
    }

  BMONum two_pi = BMONum (arcsin ("0.5", accuracy)) * "12";
  std::string angle_in_radians = (two_pi / std::to_string (n)).number;
  BMONum tan_ext_angle = tangent (angle_in_radians, accuracy);

  for (auto i = 0; i < n - 2; i++)
    {
      PointCpp &A = polygon[polygon.size () - 2];
      PointCpp &prev_pt = polygon.back ();

      // Compute slope of initial line.
      BMONum slope_initial_line = (A.y - prev_pt.y) / (A.x - prev_pt.x);

      // Compute slope and intercept of new line.
      BMONum slope_new_line, intercept_new_line;
      ComputeLine (prev_pt, slope_initial_line, tan_ext_angle, length,
                   slope_new_line, intercept_new_line);

      // Compute candidate intersection points.
      BMONum x_1, y_1, x_2, y_2;
      construct_regular_polygon_helpers::ComputeIntersectionPoints (
          prev_pt, slope_new_line, intercept_new_line, length, x_1, y_1, x_2,
          y_2, accuracy);

      // Add new point to polygon.
      polygon.push_back (construct_regular_polygon_helpers::GetCorrectPoint (
          x_1, y_1, x_2, y_2, i, n, prev_pt));
    }

  return ConvertToC (polygon);
}

construct_regular_polygon_helpers::PointCpp
construct_regular_polygon_helpers::GetCorrectPoint (BMONum &x_1, BMONum &y_1,
                                                    BMONum &x_2, BMONum &y_2,
                                                    int &i, int n,
                                                    PointCpp &prev_pt)
{
  // To decide the correct x,y pair, notice that y is never decreasing for the
  // first n / 2 sides, and is always decreasing after that.
  if (i + 1 > n / 2)
    {
      return ChooseLowerPoint (x_1, y_1, x_2, y_2, prev_pt);
    }
  bool same_height = y_1 == y_2;
  if (same_height)
    {
      return ChoosePointToLeft (x_1, y_1, x_2, y_2);
    }
  return ChooseHigherPoint (x_1, y_1, x_2, y_2, prev_pt);
}

construct_regular_polygon_helpers::PointCpp
construct_regular_polygon_helpers::ChoosePointToLeft (BMONum &x_1, BMONum &y_1,
                                                      BMONum &x_2, BMONum &y_2)
{
  if (x_1 < x_2)
    {
      return PointCpp (x_1, y_1);
    }
  return PointCpp (x_2, y_2);
}

construct_regular_polygon_helpers::PointCpp
construct_regular_polygon_helpers::ChooseHigherPoint (BMONum &x_1, BMONum &y_1,
                                                      BMONum &x_2, BMONum &y_2,
                                                      PointCpp &prev_pt)
{
  bool higher_or_equal = y_1 >= prev_pt.y;
  if (higher_or_equal)
    {
      return PointCpp (x_1, y_1);
    }
  return PointCpp (x_2, y_2);
}

construct_regular_polygon_helpers::PointCpp
construct_regular_polygon_helpers::ChooseLowerPoint (BMONum &x_1, BMONum &y_1,
                                                     BMONum &x_2, BMONum &y_2,
                                                     PointCpp &prev_pt)
{
  bool higher_or_equal = y_1 >= prev_pt.y;
  if (higher_or_equal)
    {
      return PointCpp (x_2, y_2);
    }
  return PointCpp (x_1, y_1);
}

// Computes the slope and intercept of line rotated 360/n degrees to the left
// that also passes through the previous point.
void
construct_regular_polygon_helpers::ComputeLine (PointCpp &prev_pt, BMONum &m,
                                                BMONum &tan_exterior_angle,
                                                BMONum &l, BMONum &s,
                                                BMONum &c)
{
  // Since tan(a + b) = (tan(a) + tan(b)) / (1 - tan(a) tan(b)),
  // tan(atan(m) + angle) = (m + tan(angle)) / (1 - m tan(angle))
  s = (m + tan_exterior_angle) / (BMONum ("1") - m * tan_exterior_angle);
  c = prev_pt.y - s * prev_pt.x;
}

void
construct_regular_polygon_helpers::ComputeIntersectionPoints (
    PointCpp &prev_pt, BMONum &s, BMONum &c, BMONum &l, BMONum &x_1,
    BMONum &y_1, BMONum &x_2, BMONum &y_2, size_t accuracy)
{

  BMONum sqrt_term = arithmetica::square_root (
      (BMONum ("-1") * c * c
       + c * (BMONum ("2") * prev_pt.y - BMONum ("2") * s * prev_pt.x)
       + l * l * (s * s + "1")
       - arithmetica::power ((prev_pt.y - s * prev_pt.x).number, "2",
                             accuracy))
          .number,
      accuracy);

  // We know that one of these is correct.
  x_1 = (sqrt_term - c * s + s * prev_pt.y + prev_pt.x) / (s * s + "1");
  x_2 = (BMONum ("-1") * sqrt_term - c * s + s * prev_pt.y + prev_pt.x)
        / (s * s + "1");
  y_1 = s * x_1 + c;
  y_2 = s * x_2 + c;
}

extern "C" struct point *
construct_regular_polygon (int n, const char *length, size_t accuracy)
{
  point *answer = construct_regular_polygon_cpp (n, length, accuracy);
  return answer;
}