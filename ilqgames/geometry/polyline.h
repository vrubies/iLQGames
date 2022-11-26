namespace ilqgames
{

    class Polyline2
    {
    public:
        // Construct from a list of points. This list must contain at least 2 points!
        Polyline2(const PointList2 &points);
        ~Polyline2() {}

        // Add a new point to the end of the polyline.
        void AddPoint(const Point2 &point);

        // Compute length.
        float Length() const { return length_; }

        // Find closest point on this line segment to a given point, and optionally
        // the line segment that point belongs to (and flag for whether it is a
        // vertex), and the signed squared distance, where right is positive.
        Point2 ClosestPoint(const Point2 &query, bool *is_vertex = nullptr,
                            LineSegment2 *segment = nullptr,
                            float *signed_squared_distance = nullptr,
                            bool *is_endpoint = nullptr) const;

        // Find the point the given distance from the start of the polyline.
        // Optionally returns whether this is a vertex and the line segment which the
        // point belongs to.
        Point2 PointAt(float route_pos, bool *is_vertex = nullptr,
                       LineSegment2 *segment = nullptr,
                       bool *is_endpoint = nullptr) const;

        // Access line segments.
        const std::vector<LineSegment2> &Segments() const { return segments_; }

    private:
        std::vector<LineSegment2> segments_;
        std::vector<float> cumulative_lengths_;
        float length_;
    }; // struct Polyline2

} // namespace ilqgames
