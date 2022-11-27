///////////////////////////////////////////////////////////////////////////////
//
// Line segment in 2D.
//
///////////////////////////////////////////////////////////////////////////////

#include "ilqgames/utils/defs.h"

#include <gtest/gtest.h>
#include <Eigen/Dense>
// #include <Eigen/Geometry>
// #include <Eigen/StdVector>

namespace ilqgames
{

  class LineSegment
  {
  public:
    ~LineSegment() {}
    LineSegment(const types::Point2d &point1, const types::Point2d &point2)
        : p1_(point1),
          p2_(point2),
          length_((point1 - point2).norm()),
          unit_direction_((point2 - point1) / length_)
    {
      EXPECT_GT(length_, constants::kSmallNumber);
    }

    // Accessors.
    float Length() const { return length_; }
    const types::Point2d &FirstPoint() const { return p1_; }
    const types::Point2d &SecondPoint() const { return p2_; }
    const types::Point2d &UnitDirection() const { return unit_direction_; }
    float Heading() const
    {
      return std::atan2(UnitDirection().y(), UnitDirection().x());
    }

    // Compute which side of this line segment the query point is on.
    // Returns true for the "right" side and false for the "left.""
    bool Side(const types::Point2d &query) const;

    // Find closest point on this line segment to a given point (and optionally
    // the signed squared distance, where right is positive, and whether or not
    // the closest point is an endpoint).
    types::Point2d ClosestPoint(const types::Point2d &query, bool *is_endpoint = nullptr,
                                float *signed_squared_distance = nullptr) const;

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  private:
    types::Point2d p1_;
    types::Point2d p2_;
    float length_;
    types::Point2d unit_direction_;
  }; // struct LineSegment2

} // namespace ilqgames