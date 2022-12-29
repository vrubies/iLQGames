///////////////////////////////////////////////////////////////////////////////
//
// Line segment in 2D.
//
///////////////////////////////////////////////////////////////////////////////

#include "ilqgames/geometry/line_segment.h"

namespace ilqgames
{

  bool LineSegment::Side(const Point2d &query) const
  {
    const Point2d relative_query = query - p1_;
    const float cross_product = relative_query.x() * unit_direction_.y() -
                                unit_direction_.x() * relative_query.y();

    return cross_product > 0.0;
  }

  Point2d LineSegment::ClosestPoint(const Point2d &query, bool *is_endpoint,
                                    float *signed_squared_distance) const
  {
    // Find query relative to p1.
    const Point2d relative_query = query - p1_;

    // Find dot product and signed length of cross product.
    const float dot_product = relative_query.dot(unit_direction_);
    const float cross_product = relative_query.x() * unit_direction_.y() -
                                unit_direction_.x() * relative_query.y();

    const float cross_product_sign = utils::sgn(cross_product);

    // Determine closest point. This will either be an endpoint or the interior of
    // the segment.
    if (dot_product < 0.0)
    {
      // Query lies behind this line segment, so closest point is p1.
      if (is_endpoint)
        *is_endpoint = true;

      if (signed_squared_distance)
      {
        *signed_squared_distance =
            cross_product_sign * relative_query.squaredNorm();
      }

      return p1_;
    }
    if (dot_product > length_)
    {
      // Closest point is p2.
      if (is_endpoint)
        *is_endpoint = true;

      if (signed_squared_distance)
      {
        *signed_squared_distance =
            cross_product_sign * (query - p2_).squaredNorm();
      }

      return p2_;
    }

    // Closest point is in the interior of the line segment.
    if (is_endpoint)
      *is_endpoint = false;

    if (signed_squared_distance)
      *signed_squared_distance =
          cross_product_sign * cross_product * cross_product;

    return p1_ + dot_product * unit_direction_;
  }

} // namespace ilqgames
