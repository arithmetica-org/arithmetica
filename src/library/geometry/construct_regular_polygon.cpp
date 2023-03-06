#include <cmath>
#include <vector>

#include <arithmetica.hpp>
#include <basic_math_operations.hpp>

namespace construct_regular_polygon_helpers
{
using namespace basic_math_operations;
class PointCpp
{

public:
  BMONum x = "0", y = "0";
  PointCpp (){};
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
                            const PointCpp &prev_pt);
PointCpp ChooseLowerPoint (BMONum &x_1, BMONum &y_1, BMONum &x_2, BMONum &y_2,
                           PointCpp &prev_pt);
void ComputeLine (PointCpp &prev_pt, BMONum &m, BMONum &tan_exterior_angle,
                  BMONum &s, BMONum &c);
void ComputeIntersectionPoints (PointCpp &prev_pt, BMONum &s, BMONum &c,
                                BMONum &l, BMONum &x_1, BMONum &y_1,
                                BMONum &x_2, BMONum &y_2, size_t accuracy);
point *
ConvertToC (const std::vector<PointCpp> &polygon)
{
  point *points = (point *)malloc (polygon.size () * sizeof (point));
  for (size_t i = 0; i < polygon.size (); i++)
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
} // namespace construct_regular_polygon_helpers

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

  char *two_pi_c = arcsin ("0.5", accuracy);
  BMONum two_pi = BMONum (two_pi_c) * "12";
  std::string angle_in_radians = (two_pi / std::to_string (n)).number;
  BMONum tan_ext_angle = tangent (angle_in_radians, accuracy);
  free (two_pi_c);

  for (auto i = 0; i < n - 2; i++)
    {
      PointCpp &A = polygon[i];
      PointCpp &prev_pt = polygon[i + 1];

      // Compute slope of initial line.
      BMONum slope_initial_line = (A.y - prev_pt.y) / (A.x - prev_pt.x);

      // Compute slope and intercept of new line.
      BMONum slope_new_line, intercept_new_line;
      ComputeLine (prev_pt, slope_initial_line, tan_ext_angle, slope_new_line,
                   intercept_new_line);

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
  if (y_1 == y_2)
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
    } else {
      return PointCpp (x_2, y_2);
    }
}

construct_regular_polygon_helpers::PointCpp
construct_regular_polygon_helpers::ChooseHigherPoint (BMONum &x_1, BMONum &y_1,
                                                      BMONum &x_2, BMONum &y_2,
                                                      const PointCpp &prev_pt)
{
  if (y_1 >= prev_pt.y)
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
  if (y_1 >= prev_pt.y)
    {
      return PointCpp (x_2, y_2);
    } else {
      return PointCpp (x_1, y_1);
    }
}

// Computes the slope and intercept of line rotated 360/n degrees to the left
// that also passes through the previous point.
void
construct_regular_polygon_helpers::ComputeLine (PointCpp &prev_pt, BMONum &m,
                                                BMONum &tan_exterior_angle,
                                                BMONum &s, BMONum &c)
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
  BMONum buf_7 = s*s; // s^2
  BMONum buf_8 = buf_7 + "1"; // s^2+1
  BMONum buf_9 = arithmetica::square_root (
      buf_8.number,
      accuracy); // sqrt(s^2+1)
  BMONum buf_10 = l / buf_9;

  // We know that one of these is correct.
  x_1 = prev_pt.x + buf_10;
  x_2 = prev_pt.x - buf_10;
  BMONum buf_11 = s * x_1;
  BMONum buf_12 = s * x_2;
  y_1 = buf_11 + c;
  y_2 = buf_12 + c;
}

extern "C" struct point *
construct_regular_polygon (int n, const char *length, size_t accuracy)
{
  point *answer = construct_regular_polygon_cpp (n, length, accuracy);
  return answer;
}