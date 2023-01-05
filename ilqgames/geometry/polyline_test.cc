///////////////////////////////////////////////////////////////////////////////
//
// Tests for Polyline2.
//
///////////////////////////////////////////////////////////////////////////////

#include "ilqgames/geometry/polyline.h"
#include "ilqgames/geometry/line_segment.h"

#include <gtest/gtest.h>
#include <math.h>

using namespace ilqgames;

// Check that we find the correct closest point.
TEST(PolylineTest, ClosestPointWorks)
{
  //
  //                       |
  //                       |
  //                       |
  //                       o o o o o o
  //                       o
  //  ----+-----+----+-----o----+-----+----+-----
  //                       o
  //                       o
  //                       |
  //                       |
  //                       |
  //
  const Point2d p1(0.0, -1.0);
  const Point2d p2(0.0, 1.0);
  const Point2d p3(2.0, 1.0);
  const Polyline polyline({p1, p2, p3});
  float signed_squared_distance;
  LineSegment segment(p1, p2);
  bool is_vertex;

  // Pick points to the right of the polyline.
  Point2d query(1.0, -2.0);
  Point2d closest = polyline.ClosestPoint(query, &is_vertex, &segment,
                                          &signed_squared_distance);
  EXPECT_TRUE(is_vertex);
  EXPECT_TRUE(closest.isApprox(p1));
  EXPECT_NEAR(signed_squared_distance, 2.0, constants::kSmallNumber);

  query = Point2d(0.5, 0.0);
  closest = polyline.ClosestPoint(query, &is_vertex, &segment,
                                  &signed_squared_distance);
  EXPECT_FALSE(is_vertex);
  EXPECT_LT(closest.squaredNorm(), constants::kSmallNumber);
  EXPECT_NEAR(signed_squared_distance, 0.5 * 0.5, constants::kSmallNumber);

  query = Point2d(1.5, 0.0);
  closest = polyline.ClosestPoint(query, &is_vertex, &segment,
                                  &signed_squared_distance);
  EXPECT_FALSE(is_vertex);
  EXPECT_TRUE(closest.isApprox(Point2d(1.5, 1.0)));
  EXPECT_NEAR(signed_squared_distance, 1.0, constants::kSmallNumber);

  query = Point2d(3.0, 0.0);
  closest = polyline.ClosestPoint(query, &is_vertex, &segment,
                                  &signed_squared_distance);
  EXPECT_TRUE(is_vertex);
  EXPECT_TRUE(closest.isApprox(p3));
  EXPECT_NEAR(signed_squared_distance, 2.0, constants::kSmallNumber);

  // Pick points to the left of the polyline.
  query = Point2d(-1.0, -2.0);
  closest = polyline.ClosestPoint(query, &is_vertex, &segment,
                                  &signed_squared_distance);
  EXPECT_TRUE(is_vertex);
  EXPECT_TRUE(closest.isApprox(p1));
  EXPECT_NEAR(signed_squared_distance, -2.0, constants::kSmallNumber);

  query = Point2d(-1.0, 0.0);
  closest = polyline.ClosestPoint(query, &is_vertex, &segment,
                                  &signed_squared_distance);
  EXPECT_FALSE(is_vertex);
  EXPECT_LT(closest.squaredNorm(), constants::kSmallNumber);
  EXPECT_NEAR(signed_squared_distance, -1.0, constants::kSmallNumber);

  query = Point2d(-1.0, 2.0);
  closest = polyline.ClosestPoint(query, &is_vertex, &segment,
                                  &signed_squared_distance);
  EXPECT_TRUE(is_vertex);
  EXPECT_TRUE(closest.isApprox(p2));
  EXPECT_NEAR(signed_squared_distance, -2.0, constants::kSmallNumber);

  query = Point2d(0.5, 2.0);
  closest = polyline.ClosestPoint(query, &is_vertex, &segment,
                                  &signed_squared_distance);
  EXPECT_FALSE(is_vertex);
  EXPECT_TRUE(closest.isApprox(Point2d(0.5, 1.0)));
  EXPECT_NEAR(signed_squared_distance, -1.0, constants::kSmallNumber);

  query = Point2d(3.0, 2.0);
  closest = polyline.ClosestPoint(query, &is_vertex, &segment,
                                  &signed_squared_distance);
  EXPECT_TRUE(is_vertex);
  EXPECT_TRUE(closest.isApprox(p3));
  EXPECT_NEAR(signed_squared_distance, -2.0, constants::kSmallNumber);
}
