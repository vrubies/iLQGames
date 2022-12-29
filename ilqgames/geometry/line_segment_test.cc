
#include "ilqgames/geometry/line_segment.h"

#include <gtest/gtest.h>
#include <math.h>

using namespace ilqgames;

// Check that we error out on construction if the line segment is degenerate.
TEST(LineSegmentTest, DiesIfDegenerate)
{
  // LineSegment(types::Point2d::Zero(), types::Point2d::Zero());
  EXPECT_THROW(LineSegment(Point2d::Zero(), Point2d::Zero()), std::logic_error);
}

// Check that we find the correct closest point.
TEST(LineSegmentTest, ClosestPointWorks)
{
  const Point2d lower = Point2d(0.0, -1.0);
  const Point2d upper = Point2d(0.0, 1.0);
  const LineSegment segment(lower, upper);
  float signed_squared_distance;
  bool is_endpoint;

  // Pick points in the right half plane and check closest points/distances.
  Point2d query(1.0, -2.0);
  Point2d closest =
      segment.ClosestPoint(query, &is_endpoint, &signed_squared_distance);
  EXPECT_TRUE(is_endpoint);
  EXPECT_TRUE(closest.isApprox(lower));
  EXPECT_NEAR(signed_squared_distance, 2.0, constants::kSmallNumber);

  query = Point2d(1.0, 0.0);
  closest = segment.ClosestPoint(query, &is_endpoint, &signed_squared_distance);
  EXPECT_FALSE(is_endpoint);
  EXPECT_LT(closest.squaredNorm(), constants::kSmallNumber);
  EXPECT_NEAR(signed_squared_distance, 1.0, constants::kSmallNumber);

  query = Point2d(1.0, 2.0);
  closest = segment.ClosestPoint(query, &is_endpoint, &signed_squared_distance);
  EXPECT_TRUE(is_endpoint);
  EXPECT_TRUE(closest.isApprox(upper));
  EXPECT_NEAR(signed_squared_distance, 2.0, constants::kSmallNumber);

  // Pick points in the left half plane and check closest points/distances.
  query = Point2d(-1.0, -2.0);
  closest = segment.ClosestPoint(query, &is_endpoint, &signed_squared_distance);
  EXPECT_TRUE(is_endpoint);
  EXPECT_TRUE(closest.isApprox(lower));
  EXPECT_NEAR(signed_squared_distance, -2.0, constants::kSmallNumber);

  query = Point2d(-1.0, 0.0);
  closest = segment.ClosestPoint(query, &is_endpoint, &signed_squared_distance);
  EXPECT_FALSE(is_endpoint);
  EXPECT_LT(closest.squaredNorm(), constants::kSmallNumber);
  EXPECT_NEAR(signed_squared_distance, -1.0, constants::kSmallNumber);

  query = Point2d(-1.0, 2.0);
  closest = segment.ClosestPoint(query, &is_endpoint, &signed_squared_distance);
  EXPECT_TRUE(is_endpoint);
  EXPECT_TRUE(closest.isApprox(upper));
  EXPECT_NEAR(signed_squared_distance, -2.0, constants::kSmallNumber);
}