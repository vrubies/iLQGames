///////////////////////////////////////////////////////////////////////////////
//
// Line segment in 2D.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef ILQGAMES_GEOMETRY_LINE_SEGMENT2_H
#define ILQGAMES_GEOMETRY_LINE_SEGMENT2_H

#include "ilqgames/utils/defs.h"

#include <gtest/gtest.h>
#include <Eigen/Dense>
// #include <Eigen/Geometry>
// #include <Eigen/StdVector>

using ilqgames::types::Point2d;

namespace ilqgames
{

  class LineSegment
  {
  public:
    ~LineSegment() {}
    LineSegment(const Point2d &point1, const Point2d &point2)
        : p1_(point1),
          p2_(point2),
          length_((point1 - point2).norm()),
          unit_direction_((point2 - point1) / length_)
    {
      if (length_ <= constants::kSmallNumber)
      {
        throw std::logic_error("point1 and point2 are equal or too close.");
      }
      // std::cout << (length_ > constants::kSmallNumber) << std::endl;
    }

    // Accessors.
    float Length() const { return length_; }
    const Point2d &FirstPoint() const { return p1_; }
    const Point2d &SecondPoint() const { return p2_; }
    const Point2d &UnitDirection() const { return unit_direction_; }
    float Heading() const
    {
      return std::atan2(UnitDirection().y(), UnitDirection().x());
    }

    // Compute which side of this line segment the query point is on.
    // Returns true for the "right" side and false for the "left.""
    bool Side(const Point2d &query) const;

    // Find closest point on this line segment to a given point (and optionally
    // the signed squared distance, where right is positive, and whether or not
    // the closest point is an endpoint).
    Point2d ClosestPoint(const Point2d &query, bool *is_endpoint = nullptr,
                         float *signed_squared_distance = nullptr) const;

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  private:
    Point2d p1_;
    Point2d p2_;
    float length_;
    Point2d unit_direction_;
  }; // struct LineSegment2

} // namespace ilqgames

#endif