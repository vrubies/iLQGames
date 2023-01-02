#include "ilqgames/geometry/polyline.h"

namespace ilqgames
{

  Polyline::Polyline(const types::PointList2d &points)
  {
    size_t num_points = points.size();
    if (num_points < 2)
    {
      throw std::logic_error("Needs at least 2 points to form a polyline.");
    }

    cumulative_lengths_.push_back(0.0);
    for (size_t i = 1; i < num_points; i++)
    {
      segments_.emplace_back(points[i - 1], points[i]);
      cumulative_lengths_.push_back(segments_.back().Length());
    }
    length_ = cumulative_lengths_.back();
  }

  void Polyline::AddPoint(const types::Point2d &point)
  {
    const auto end_point = segments_.back().SecondPoint();
    segments_.emplace_back(end_point, point);
  }

  // Point2d Polyline::ClosestPoint(
  //     const Point2d &query, bool *is_vertex = nullptr,
  //     LineSegment *segment = nullptr,
  //     float *signed_squared_distance = nullptr,
  //     bool *is_endpoint = nullptr)
  // {
  //   // Go through segments and find closest one.
  //   segment = &segments_.front();
  //   float closest_so_far = std::numeric_limits<float>::infinity();
  //   std::unique_ptr<float> dist_ptr;
  //   for (const auto &tmp_segment : segments_)
  //   {
  //     *tmp_segment.ClosestPoint(query, is_vertex, dist_ptr);
  //     if (*dist_ptr < closest_so_far)
  //     {
  //       closest_so_far = *dist_ptr;
  //       segment = &tmp_segment;
  //     }
  //   }

  //   if ()
  // }
}