///////////////////////////////////////////////////////////////////////////////
//
// Polyline2 class for piecewise linear paths in 2D.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef ILQGAMES_GEOMETRY_POLYLINE2_H
#define ILQGAMES_GEOMETRY_POLYLINE2_H

#include "ilqgames/geometry/line_segment.h"

// #include <glog/logging.h>
#include <math.h>

namespace ilqgames
{

  class Polyline
  {
  public:
    // Construct from a list of points. This list must contain at least 2 points!
    Polyline(const types::PointList2d &points);
    ~Polyline() {}

    // Add a new point to the end of the polyline.
    void AddPoint(const types::Point2d &point);

    // Compute length.
    float Length() const { return length_; }

    // Find closest point on this line segment to a given point, and optionally
    // the line segment that point belongs to (and flag for whether it is a
    // vertex), and the signed squared distance, where right is positive.
    types::Point2d ClosestPoint(const types::Point2d &query, bool *is_vertex = nullptr,
                                LineSegment *segment = nullptr,
                                float *signed_squared_distance = nullptr,
                                bool *is_endpoint = nullptr) const;

    // Find the point the given distance from the start of the polyline.
    // Optionally returns whether this is a vertex and the line segment which the
    // point belongs to.
    types::Point2d PointAt(float route_pos, bool *is_vertex = nullptr,
                           LineSegment *segment = nullptr,
                           bool *is_endpoint = nullptr) const;

    // Access line segments.
    const std::vector<LineSegment> &Segments() const { return segments_; }

  private:
    std::vector<LineSegment> segments_;
    std::vector<float> cumulative_lengths_;
    float length_;
  }; // struct Polyline

} // namespace ilqgames

#endif
