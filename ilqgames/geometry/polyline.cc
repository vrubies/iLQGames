#include "ilqgames/geometry/polyline.h"
#include <glog/logging.h>

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

  Point2d Polyline::ClosestPoint(
      const Point2d &query, bool *is_vertex,
      LineSegment *segment,
      float *signed_squared_distance,
      bool *is_endpoint) const
  {
    // Go through segments and find closest one.
    Point2d closest_point;
    Point2d current_point;
    *signed_squared_distance = std::numeric_limits<float>::infinity();
    float current_dist;
    bool vertex;
    for (auto &tmp_segment : segments_)
    {
      current_point = tmp_segment.ClosestPoint(query, &vertex, &current_dist);
      if (current_dist < std::abs(*signed_squared_distance))
      {
        closest_point = current_point;
        *signed_squared_distance = current_dist;
        *segment = tmp_segment;
        *is_vertex = vertex;
      }
    }
    // segment = return_segment.get();

    if (segment == &segments_.back())
    {
      *is_endpoint = *is_vertex && closest_point.isApprox(segment->SecondPoint());
    }
    if (segment == &segments_.front())
    {
      *is_endpoint = *is_vertex && closest_point.isApprox(segment->FirstPoint());
    }
    return closest_point;
  }

  Point2d Polyline::PointAt(
      float route_pos, bool *is_vertex,
      LineSegment *segment,
      bool *is_endpoint) const
  {
    // Check if route_pos is longer than polyline.
    if (route_pos > cumulative_lengths_.back())
    {
      LOG(WARNING) << "Route position " << route_pos
                   << " was off the end of the route. Returning endpoint.";
      *is_vertex = true;
      *segment = segments_.back();
      *is_endpoint = true;
      return segments_.back().SecondPoint();
    }

    auto it = std::upper_bound(cumulative_lengths_.begin(),
                               cumulative_lengths_.end(), route_pos);
    it--;
    const size_t idx = std::distance(cumulative_lengths_.begin(), it);
    *segment = segments_[idx];
    const float remaining = route_pos - cumulative_lengths_[idx];
    *is_vertex = remaining < constants::kSmallNumber ||
                 remaining > segments_[idx].Length();
    return segments_[idx].FirstPoint() + remaining * segments_[idx].UnitDirection();
  }
}