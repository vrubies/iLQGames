///////////////////////////////////////////////////////////////////////////////
//
// Line segment in 2D.
//
///////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include <Eigen/Dense>
// #include <Eigen/Geometry>
// #include <Eigen/StdVector>

namespace ilqgames
{
  // Small number for use in approximate equality checking.
  static constexpr float kSmallNumber = 1e-4;

  class LineSegment
  {
  public:
    ~LineSegment() {}
    LineSegment(const Eigen::Vector2f &point1, const Eigen::Vector2f &point2)
        : p1_(point1),
          p2_(point2),
          length_((point1 - point2).norm()),
          unit_direction_((point2 - point1) / length_)
    {
      EXPECT_GT(length_, kSmallNumber);
    }

    // Accessors.
    float Length() const { return length_; }
    const Eigen::Vector2f &FirstPoint() const { return p1_; }
    const Eigen::Vector2f &SecondPoint() const { return p2_; }
    const Eigen::Vector2f &UnitDirection() const { return unit_direction_; }
    float Heading() const
    {
      return std::atan2(UnitDirection().y(), UnitDirection().x());
    }

    // Compute which side of this line segment the query point is on.
    // Returns true for the "right" side and false for the "left.""
    bool Side(const Eigen::Vector2f &query) const;

    // Find closest point on this line segment to a given point (and optionally
    // the signed squared distance, where right is positive, and whether or not
    // the closest point is an endpoint).
    Eigen::Vector2f ClosestPoint(const Eigen::Vector2f &query, bool *is_endpoint = nullptr,
                                 float *signed_squared_distance = nullptr) const;

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  private:
    Eigen::Vector2f p1_;
    Eigen::Vector2f p2_;
    float length_;
    Eigen::Vector2f unit_direction_;
  }; // struct LineSegment2

} // namespace ilqgames